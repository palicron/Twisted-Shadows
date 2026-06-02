// Twisted Shadow make by JSP


#include "Controllers/TS_PlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "TwistedShadows.h"
#include "Actors/Camera/TS_CameraActor.h"
#include "Camera/CameraActor.h"
#include "Engine/DecalActor.h"
#include "Interfaces/TS_Interactable.h"
#include "Kismet/GameplayStatics.h"
#include "Tracks/MovieSceneMaterialTrack.h"

ATS_PlayerController::ATS_PlayerController()
{
	bIsInShadowCasting = false;
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
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Some debug message!"));	
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

void ATS_PlayerController::OnShadowCastInput(const FInputActionValue& Value)
{
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (!Subsystem)
	{
		return;
	}
	if (bIsInShadowCasting)
	{
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
		bIsInShadowCasting = false;
		Subsystem->RemoveMappingContext(ShadowCastMappingContexts);
		Subsystem->AddMappingContext(DefaultMappingContexts, 0);
		GetWorld()->GetTimerManager().ClearTimer(ShadowCastMouseTrackHandle);
		return;
	}
	
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

void ATS_PlayerController::OnShadowClickInput(const FInputActionValue& Value)
{
	float MouseX;
	float MouseY;
	
	GetMousePosition(MouseX, MouseY);
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Click :::: X%f ||| Y %f "), MouseX,MouseY));
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
		//DrawDebugSphere(GetWorld(), HitLocation, 100.f, 12.f,FColor::Green, false, 0.1f,1);
		return;
	}
	
	if (DecalActor)
	{
		DecalActor->SetActorHiddenInGame(true);
		
	}
	//DrawDebugSphere(GetWorld(), HitLocation, 100.f, 12.f,FColor::Red, false, 0.1f,1);

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

