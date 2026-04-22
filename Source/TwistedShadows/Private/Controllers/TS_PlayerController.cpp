// Twisted Shadow make by JSP


#include "Controllers/TS_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Actors/Camera/TS_CameraActor.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

ATS_PlayerController::ATS_PlayerController()
{
}

void ATS_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACameraActor::StaticClass(), CameraActors);
	
	if (CameraActors.Num() > 0)
	{
		CurrentCameraActor = Cast<ATS_CameraActor>(CameraActors[0]);
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
}
