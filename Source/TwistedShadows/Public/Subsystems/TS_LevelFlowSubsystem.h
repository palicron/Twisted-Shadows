// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions/GeneralDefinitions.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TS_LevelFlowSubsystem.generated.h"

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
	void LoadLevel(const int32 LevelID);
	
	UFUNCTION(BlueprintCallable)
	void LoadNextLevel();
	
	UFUNCTION(BlueprintCallable)
	void LoadMainMenu();
	
	UFUNCTION(BlueprintCallable)
	void ReloadLevel();
	
	//  need to add get next and previs level info
	
	UFUNCTION(BlueprintCallable)
	FLevelProgress GetLevelProgressInfo(const int32 LevelID,bool& bFindInfo) const;
protected:
	
	TMap<int32, FLevelProgress> Levels;
	
	
};
