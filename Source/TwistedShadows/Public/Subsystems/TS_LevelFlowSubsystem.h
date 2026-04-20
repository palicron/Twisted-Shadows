// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions/GeneralDefinitions.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TS_LevelFlowSubsystem.generated.h"

class UTS_SaveSubsystem;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_LevelFlowSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	UFUNCTION(BlueprintCallable)
	void StartNewGame(const int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	void LoadLevel(const int32 LevelID);
	
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void ReloadLevel();
	
	UFUNCTION()
	void ContinueGame();
	
	//  need to add get next and previs level info
	
	UFUNCTION(BlueprintCallable)
	FLevelProgress GetLevelProgressInfo(const int32 LevelID,bool& bFindInfo) const;

	int32 GetCurrentLevelID() const { return CurrentLevelID; }
protected:
	
	int32 CurrentLevelID;
	int32 LastLevelID;
	int32 NewGameLevelIndex;
	int32 MainMenuLevelIndex;
	int32 CurrentSlotIndex;
	
	TMap<int32, FLevelProgress> Levels;
	
	TWeakObjectPtr<UTS_SaveSubsystem> SaveSubsystemPtr;
	
	void OnWorldReady(UWorld* World, const UWorld::InitializationValues);
	
	
};
