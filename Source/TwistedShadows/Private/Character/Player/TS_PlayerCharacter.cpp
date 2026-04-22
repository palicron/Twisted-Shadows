// Twisted Shadow make by JSP


#include "Character/Player/TS_PlayerCharacter.h"

#include "Actors/Camera/TS_CameraActor.h"
#include "Controllers/TS_PlayerController.h"


ATS_PlayerCharacter::ATS_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

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

}

void ATS_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	PlayerController = Cast<ATS_PlayerController>(NewController);
	
	if (!PlayerController.IsValid())
	{
		return;
	}
	
	CurrentCamera = PlayerController->GetCurrentCamera();
	
	if (!CurrentCamera.IsValid())
	{
		return;
	}
	
	CurrentForwardVector = CurrentCamera->GetCameraForwardVector();
	CurrentRightVector = CurrentCamera->GetCameraRightVector();
}

