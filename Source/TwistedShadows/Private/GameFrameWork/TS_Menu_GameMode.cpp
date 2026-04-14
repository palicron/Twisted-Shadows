// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/TS_Menu_GameMode.h"

void ATS_Menu_GameMode::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	
	if (!PlayerController)
	{
		return;
	}
	
	PlayerController->SetInputMode(FInputModeUIOnly());
}
