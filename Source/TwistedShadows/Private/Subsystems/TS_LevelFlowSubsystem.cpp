// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TS_LevelFlowSubsystem.h"

#include "Data/TS_LevelDefinitionDataAsset.h"
#include "GameFrameWork/TS_GameInstance.h"
#include "Kismet/GameplayStatics.h"

void UTS_LevelFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	if (const UTS_GameInstance* GI = Cast<UTS_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (GI->LevelDefinitions)
		{
			for (const FLevelDefinition& Level : GI->LevelDefinitions->LevelDefinitions)
			{
				FLevelProgress NewProgress;
				NewProgress.LevelID = Level.LevelID;
				NewProgress.LevelName = Level.LevelName;
				NewProgress.LevelDescription = Level.LevelDescription;
				Levels.Add(Level.LevelID, NewProgress);
			}
		}
	}
}
void UTS_LevelFlowSubsystem::LoadLevel(const int32 LevelID)
{
}

void UTS_LevelFlowSubsystem::LoadNextLevel()
{
}

void UTS_LevelFlowSubsystem::LoadMainMenu()
{
}

void UTS_LevelFlowSubsystem::ReloadLevel()
{
}

FLevelProgress UTS_LevelFlowSubsystem::GetLevelProgressInfo(const int32 LevelID, bool& bFindInfo) const
{
	if (!Levels.Contains(LevelID))
	{
		bFindInfo = false;
		return FLevelProgress();
	}

	bFindInfo = true;
	return Levels[LevelID];
}
