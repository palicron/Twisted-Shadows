// Twisted Shadow make by JSP


#include "Character/Player/TS_PlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "Actors/Camera/TS_CameraActor.h"
#include "Component/Interact/TS_InteractComponent.h"
#include "Controllers/TS_PlayerController.h"


ATS_PlayerCharacter::ATS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	PlayerInteractComponent = CreateDefaultSubobject<UTS_InteractComponent>("Player Interact Component");

	CurrentMovementType = ETS_MovementType::Normal;
}


void ATS_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATS_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATS_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATS_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ATS_PlayerCharacter::StartedInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ATS_PlayerCharacter::OngoingInteract);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Completed, this, &ATS_PlayerCharacter::EndInteract);
	}

}

void ATS_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	PlayerController = Cast<ATS_PlayerController>(NewController);
	
	if (!PlayerController.IsValid())
	{
		return;
	}
	PlayerController->OnCameraChangedDelegate.AddUniqueDynamic(this,&ATS_PlayerCharacter::OnCameraChangeCallback);
	CurrentCamera = PlayerController->GetCurrentCamera();

	if (!CurrentCamera.IsValid())
	{
		return;
	}

	CurrentForwardVector = CurrentCamera->GetCameraForwardVector();
	CurrentRightVector = CurrentCamera->GetCameraRightVector();
}

void ATS_PlayerCharacter::OnGoalTouch()
{
}

void ATS_PlayerCharacter::StartGrabbingActor(AActor* ActorToGrab, USceneComponent* GrabbingPoint, const ETS_MovementType MovementType)
{
	
	if (!ActorToGrab || !GrabbingPoint)
	{
		return;
	}
	GrabbedActor = ActorToGrab;
	StartPosition = GrabbingPoint->GetComponentLocation();
	StartPosition.Z = GetActorLocation().Z;
	CurrentMovementType = MovementType;
	
	MoveToGrabPoint(GrabbingPoint);
}

void ATS_PlayerCharacter::MoveToGrabPoint(USceneComponent* GrabbingPoint)
{
	FTimerDelegate MoveDelegate;
	MoveDelegate.BindWeakLambda(this,[&]()
	{
		const FVector NewPosition = FMath::VInterpTo(StartPosition,GetActorLocation(),0.1f,0.1f);
		SetActorLocation(NewPosition);
		
		if (FVector::Distance(StartPosition,GetActorLocation()) < 10.f)
		{
			SetActorLocation(StartPosition);
			GetWorld()->GetTimerManager().ClearTimer(GrabbingTimerHandle);
			if(GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Orange, TEXT("Some debug message!"));	
		}
	});
	
	GetWorld()->GetTimerManager().SetTimer(GrabbingTimerHandle,MoveDelegate,0.1f,true);

}

void ATS_PlayerCharacter::EndeGrabbingActor()
{
	CurrentMovementType = ETS_MovementType::Normal;
	GrabbedActor = nullptr;
	
}


void ATS_PlayerCharacter::Move(const FInputActionValue& Value)
{
	if (CurrentMovementType != ETS_MovementType::Normal)
	{
		return;
	}
	FVector2D InputVector = Value.Get<FVector2D>();
	
	AddMovementInput(CurrentForwardVector, InputVector.X);
	AddMovementInput(CurrentRightVector, InputVector.Y);
}


void ATS_PlayerCharacter::StartedInteract(const FInputActionValue& Value)
{
	PlayerInteractComponent->StartedActivateInteract();
}

void ATS_PlayerCharacter::OngoingInteract(const FInputActionInstance& Value)
{
	PlayerInteractComponent->OngoingActivateInteract(Value.GetElapsedTime());
}

void ATS_PlayerCharacter::EndInteract(const FInputActionValue& Value)
{
	PlayerInteractComponent->EndActivateInteract();
}


void ATS_PlayerCharacter::OnCameraChangeCallback(ATS_CameraActor* NewCamera)
{
	if (!NewCamera)
	{
		return;
	}
	
	CurrentCamera = NewCamera;
	CurrentForwardVector = CurrentCamera->GetCameraForwardVector();
	CurrentRightVector = CurrentCamera->GetCameraRightVector();
}
