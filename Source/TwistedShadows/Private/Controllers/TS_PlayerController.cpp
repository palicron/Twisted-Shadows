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
}

void ATS_PlayerController::SetNewCamera(ATS_CameraActor* NewCamera)
{
	CurrentCameraActor = NewCamera;

	if (CurrentCameraActor.IsValid())
	{
		OnCameraChangedDelegate.Broadcast(CurrentCameraActor.Get());
	}
}
