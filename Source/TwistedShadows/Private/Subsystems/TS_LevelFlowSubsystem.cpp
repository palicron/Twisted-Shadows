// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TS_LevelFlowSubsystem.h"

#include "Data/TS_LevelDefinitionDataAsset.h"
#include "GameFrameWork/TS_GameInstance.h"
#include "GameFrameWork/TS_WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/TS_SaveSubsystem.h"

void UTS_LevelFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	NewGameLevelIndex = 0;
	CurrentSlotIndex = 0;
	if (const UTS_GameInstance* GI = Cast<UTS_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		if (GI->LevelDefinitions)
		{
			NewGameLevelIndex = GI->LevelDefinitions->StartingLevelIndex;
			MainMenuLevelIndex = GI->LevelDefinitions->MainMenuLevelIndex;
			
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
		
		SaveSubsystemPtr = GI->GetSubsystem<UTS_SaveSubsystem>();
	}
	
	FWorldDelegates::OnPostWorldInitialization.AddUObject(this,&UTS_LevelFlowSubsystem::OnWorldReady);
}

void UTS_LevelFlowSubsystem::StartNewGame(const int32 SlotIndex)
{
	CurrentSlotIndex = SlotIndex;
	//For the moment is just the laod of level pro y will need to set up new slot and save before starting a new game
	if (SaveSubsystemPtr.IsValid() && SaveSubsystemPtr->GetGlobalSaveGame())
	{
		SaveSubsystemPtr->GetGlobalSaveGame()->LastUsedSlotIndex = SlotIndex;
		SaveSubsystemPtr->SaveGeneralData();
		SaveSubsystemPtr->InitNewSlotGame(SlotIndex);
	}

	LoadLevel(NewGameLevelIndex);
}

void UTS_LevelFlowSubsystem::LoadLevel(const int32 LevelID)
{
	if (!Levels.Contains(LevelID) || !Levels[LevelID].LevelAsset.ToSoftObjectPath().IsValid())
	{
		return;
	}

	LastLevelID = CurrentLevelID;
	CurrentLevelID = Levels[LevelID].LevelID;
	//TODO REMEVER NEED A FADE and save game 
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
	//TODO SAME NEED TRACITION AND SAVE FOR THE MOMENOT ONLY TRAVEl
	LoadLevel(MainMenuLevelIndex);
}

void UTS_LevelFlowSubsystem::ReloadLevel()
{
	LoadLevel(CurrentLevelID);
}

void UTS_LevelFlowSubsystem::ContinueGame()
{
	if (!SaveSubsystemPtr.IsValid())
	{
		return;
	}

	if (const UTS_GlobalSaveGame* Save = SaveSubsystemPtr->GetGlobalSaveGame())
	{
		if (Save->SlotSummaries.Contains(CurrentSlotIndex))
		{
			LoadLevel(Save->SlotSummaries[CurrentSlotIndex].NextLevelIndex);
		}
	}
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
