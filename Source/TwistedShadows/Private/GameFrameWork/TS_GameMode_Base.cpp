// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/TS_GameMode_Base.h"

#include "GameFrameWork/TS_GameState.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/TS_SaveSubsystem.h"
#include "UI/HUD/TS_PlayerHUD.h"

void ATS_GameMode_Base::EndLevel(ACharacter* EndPlayer)
{
	
	//END LEVEL

	if (ATS_GameState* GS = GetGameState<ATS_GameState>())
	{
		GS->EndLevelTimer();
	}
	
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC)
	{
		return;
	}

	//TODO THIS SHOULD BE IN THE PC ASS A HOLD and getting the new WIDget to get foce
	PC->SetInputMode(FInputModeUIOnly());
	PC->SetShowMouseCursor(true);

	if (UTS_SaveSubsystem* Save = UGameplayStatics::GetGameInstance(this)->GetSubsystem<UTS_SaveSubsystem>())
	{
		Save->SaveData();
	}

	ATS_PlayerHUD* PlayerHUD = Cast<ATS_PlayerHUD>(PC->GetHUD());
	
	PlayerHUD->DisplayEndLevelWidget();
	
	//GET player controller and HUD
	//Disable player Controller for game
	// Display New HUD of ending level
	
}
