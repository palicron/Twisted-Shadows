// Twisted Shadow make by JSP


#include "Controllers/TS_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TwistedShadows.h"
#include "Actors/Camera/TS_CameraActor.h"
#include "Camera/CameraActor.h"
#include "Character/Player/TS_CasterCharacter.h"
#include "Character/Player/TS_ShadowCharacter.h"

#include "Engine/DecalActor.h"
#include "Interfaces/TS_Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Tracks/MovieSceneMaterialTrack.h"

ATS_PlayerController::ATS_PlayerController()
{
	bIsInShadowCasting = false;
	CurrentShadowCastingState = ETS_ShadowCastingState::None;
	
	ShadowMaxCastingDistance = 450.f;
	ShadowMinCastingDistance = 125.f;
}


void ATS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
	
	if (DecalActorClass)
	{
		
		DecalActor = GetWorld()->SpawnActor<ADecalActor>(DecalActorClass);
		DecalActor->SetActorScale3D(FVector(0.2f));
		DecalActor->SetActorHiddenInGame(true);
	}

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	
	if (CameraActors.Num() > 0)
	{
		SetNewCamera(Cast<ATS_CameraActor>(CameraActors[0]));
	}

	if (CurrentCameraActor.IsValid())
	{
		SetViewTargetWithBlend(CurrentCameraActor.Get(), 0.f);
	}
}

void ATS_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContexts, 0);
		}
	}
	
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	
	Input->BindAction(ShadowCastInput,ETriggerEvent::Started,this,&ATS_PlayerController::OnShadowCastInput);
	Input->BindAction(ShadowClickInput,ETriggerEvent::Started,this,&ATS_PlayerController::OnShadowClickInput);
}

void ATS_PlayerController::ToggleShadowCasting()
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem )
	{
		return;
	}
	
	if (bIsInShadowCasting)
	{
		CurrentShadowCastingState = ETS_ShadowCastingState::None;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		bIsInShadowCasting = false;
		Subsystem->RemoveMappingContext(ShadowCastMappingContexts);
		Subsystem->AddMappingContext(DefaultMappingContexts, 0);
		GetWorld()->GetTimerManager().ClearTimer(ShadowCastMouseTrackHandle);
		return;
	}
	
	CurrentShadowCastingState = ETS_ShadowCastingState::Casting;
	bShowMouseCursor = true;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	InputMode.SetHideCursorDuringCapture(false);
	SetInputMode(InputMode);
	Subsystem->RemoveMappingContext(DefaultMappingContexts);
	Subsystem->AddMappingContext(ShadowCastMappingContexts, 0);
	
	GetWorld()->GetTimerManager().SetTimer(ShadowCastMouseTrackHandle,this,&ATS_PlayerController::MouseTrackShadowCast,0.05f,{.bLoop = true,.bMaxOncePerFrame = true});
	bIsInShadowCasting = true;
}

void ATS_PlayerController::OnShadowCastInput(const FInputActionValue& Value)
{
	APawn* PossesPawn = GetPawn();
	if (PossesPawn && PossesPawn->IsA<ATS_CasterCharacter>())
	{
		ToggleShadowCasting();
	}
	else
	{
		DestroyShadow();
	}
}

void ATS_PlayerController::OnShadowClickInput(const FInputActionValue& Value)
{
	if (CurrentShadowCastingState != ETS_ShadowCastingState::Casting)
	{
		return;
	}

	CurrentShadowCastingState = ETS_ShadowCastingState::None;
	DecalActor->SetActorHiddenInGame(true);
	SpawnAndPossesShadow();
	ToggleShadowCasting();
}


void ATS_PlayerController::SetNewCamera(ATS_CameraActor* NewCamera)
{
	CurrentCameraActor = NewCamera;

	if (CurrentCameraActor.IsValid())
	{
		OnCameraChangedDelegate.Broadcast(CurrentCameraActor.Get());
	}
}

void ATS_PlayerController::MouseTrackShadowCast()
{
	FVector HitLocation = FVector::ZeroVector;
	bool bHit = GetLocationUnderCursor(HitLocation);
	

	if (!bHit)
	{
		CurrentShadowCastingState = ETS_ShadowCastingState::InvalidFloor;
		return;
	}
	
	float DistanceToCaster = (GetPawn()->GetActorLocation() - HitLocation).Size();
	
	if (FMath::Abs(DistanceToCaster) > ShadowMaxCastingDistance || FMath::Abs(DistanceToCaster) < ShadowMinCastingDistance)
	{
		CurrentShadowCastingState = ETS_ShadowCastingState::Block;
		DecalActor->SetActorHiddenInGame(true);
		return;
	}

	FHitResult Overlaps;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(50.f);
	bool bOverlap = GetWorld()->SweepSingleByChannel(
		Overlaps,
		HitLocation,
		HitLocation,
		FQuat::Identity,
		SHADOW_BLOCK_TRACE_CHANNEL,
		Sphere,
		FCollisionQueryParams()
	);
	
	if (!bOverlap)
	{
		if (DecalActor)
		{
			DecalActor->SetActorHiddenInGame(false);
			DecalActor->SetActorLocation(HitLocation);
		}
		CurrentShadowCastingState = ETS_ShadowCastingState::Casting;
		return;
	}
	
	if (DecalActor)
	{
		CurrentShadowCastingState = ETS_ShadowCastingState::Block;
		DecalActor->SetActorHiddenInGame(true);
		
	}
	
}

bool ATS_PlayerController::GetLocationUnderCursor(FVector& Location)
{
	// trace the visibility channel at the cursor location
	FHitResult OutHit;

	GetHitResultUnderCursorByChannel(SelectionTraceChannel, true, OutHit);

	// if there was a blocking hit, return the hit location
	if (OutHit.bBlockingHit)
	{
		Location = OutHit.Location;
		return true;
	}

	return OutHit.bBlockingHit;
}

void ATS_PlayerController::SpawnAndPossesShadow()
{
	FVector HitLocation = FVector::ZeroVector;
	bool bHit = GetLocationUnderCursor(HitLocation);
	

	if (!bHit || !ShadowCharacterClass)
	{
		return;
	}
	HitLocation.Z += 100.f;
	FTransform NewTransform;
	NewTransform.SetLocation(HitLocation);
	
	ShadowCharacter = GetWorld()->SpawnActorDeferred<ATS_ShadowCharacter>(ShadowCharacterClass,NewTransform,this,GetPawn());
	ShadowCharacter->FinishSpawning(NewTransform);
	LastCaster = Cast<ATS_CasterCharacter>(GetPawn());
	ShadowCharacter->OnShadowDestroyDelegate.AddDynamic(this,&ATS_PlayerController::PossessLastCaster);
	Possess(ShadowCharacter.Get());
	ShadowCharacter->SetUpShadowInfo(LastCaster.Get(), HitLocation);
	if (CurrentCameraActor.IsValid())
	{
		SetViewTargetWithBlend(CurrentCameraActor.Get(), 0.f);
	}
}

void ATS_PlayerController::PossessLastCaster()
{
	if (CurrentCameraActor.IsValid())
	{
		Possess(LastCaster.Get());
		SetViewTargetWithBlend(CurrentCameraActor.Get(), 0.f);
	}
}

void ATS_PlayerController::DestroyShadow()
{
	if (ShadowCharacter.IsValid() && LastCaster.IsValid())
	{
		PossessLastCaster();
		ShadowCharacter->DestroyShadow();
		ShadowCharacter = nullptr;
	}
}

