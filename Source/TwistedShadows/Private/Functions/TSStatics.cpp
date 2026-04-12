// Fill out your copyright notice in the Description page of Project Settings.


#include "Functions/TSStatics.h"

#include "GameFrameWork/TS_GameState.h"
#include "Kismet/GameplayStatics.h"

UMVVM_LevelFlow* UTSStatics::GetLevelFlowViewModel(const UObject* WorldContextObject)
{
	if (!WorldContextObject)
	{
		return nullptr;
	}

	if (const ATS_GameState* GameState = Cast<ATS_GameState>(UGameplayStatics::GetGameState(WorldContextObject)))
	{
		return GameState->GetLevelFlowViewModel();
	}

	return nullptr;
}

FText UTSStatics::GetLevelTimeInTextFormat(const float TimeInSec)
{
	int32 Minutes = FMath::FloorToInt(TimeInSec / 60.f);
	int32 Seconds = FMath::FloorToInt(TimeInSec) % 60;
	
	return FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds));
}
