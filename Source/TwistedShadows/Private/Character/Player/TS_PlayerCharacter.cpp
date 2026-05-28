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
	PlayerController->OnCameraChangedDelegate.AddDynamic(this,&ATS_PlayerCharacter::OnCameraChangeCallback);
	CurrentCamera = PlayerController->GetCurrentCamera();

	if (!CurrentCamera.IsValid())
	{
		return;
	}

	CurrentForwardVector = CurrentCamera->GetCameraForwardVector();
	CurrentRightVector = CurrentCamera->GetCameraRightVector();
}


void ATS_PlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D InputVector = Value.Get<FVector2D>();
	
	AddMovementInput(CurrentForwardVector, InputVector.X);
	AddMovementInput(CurrentRightVector, InputVector.Y);
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
