// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TS_LevelFlowSubsystem.h"

#include "Data/TS_LevelDefinitionDataAsset.h"
#include "GameFrameWork/TS_GameInstance.h"
#include "GameFrameWork/TS_WorldSettings.h"
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
				NewProgress.NextLevelID = Level.NextLevelID;
				NewProgress.PreviousLevelID = Level.PreviousLevelID;
				NewProgress.LevelName = Level.LevelName;
				NewProgress.LevelDescription = Level.LevelDescription;
				NewProgress.LevelAsset = Level.LevelAsset;
				
				
				Levels.Add(Level.LevelID, NewProgress);
			}
		}
	}
	
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this,&UTS_LevelFlowSubsystem::OnWorldReady);
}

void UTS_LevelFlowSubsystem::LoadLevel(const int32 LevelID)
{
	if (!Levels.Contains(LevelID) || !Levels[LevelID].LevelAsset.ToSoftObjectPath().IsValid())
	{
		return;
	}

	LastLevelID = CurrentLevelID;
	CurrentLevelID = Levels[LevelID].LevelID;
	//TODO REMEVER NEED A FADE 
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Levels[LevelID].LevelAsset, true);
}

void UTS_LevelFlowSubsystem::LoadNextLevel()
{
	if (!Levels.Contains(CurrentLevelID) || !Levels.Contains(Levels[CurrentLevelID].NextLevelID))
	{
		return;
	}

	LoadLevel(Levels[CurrentLevelID].NextLevelID);
}

void UTS_LevelFlowSubsystem::LoadMainMenu()
{
}

void UTS_LevelFlowSubsystem::ReloadLevel()
{
	LoadLevel(CurrentLevelID);
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

void UTS_LevelFlowSubsystem::OnWorldReady(UWorld* World, const UWorld::InitializationValues)
{
	if (World && World->IsGameWorld())
	{
		ATS_WorldSettings* Settings = Cast<ATS_WorldSettings>(World->GetWorldSettings());
		
		if (!Settings)
		{
			return;
		}
		
		CurrentLevelID = Settings->LevelID;
		LastLevelID = -5;;
		if(GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, 
				FString::Printf(TEXT("World Ready Whit id  %d"), CurrentLevelID));
	}
}
