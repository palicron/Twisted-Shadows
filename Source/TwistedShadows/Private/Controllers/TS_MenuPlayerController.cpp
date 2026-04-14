// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TS_MenuPlayerController.h"

#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

void ATS_MenuPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = true;
	
	TArray<AActor*> CameraActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACameraActor::StaticClass(),CameraActors);
	
	ACameraActor* CameraActor = nullptr;
	
	if (CameraActors.Num() > 0)
	{
		CameraActor = Cast<ACameraActor>(CameraActors[0]);
	}
	
	if (CameraActor)
	{
		SetViewTargetWithBlend(CameraActor, 0.f);
	}
}
