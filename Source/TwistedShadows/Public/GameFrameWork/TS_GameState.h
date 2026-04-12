// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TS_GameState.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	
	ATS_GameState();
protected:
	
	float StartDelayTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Level Time")
	float LevelInitialTime;
	
	float LevelEndTime;
	
	float LevelTimer;
	
	float PauseStartTime;
	
	float TotalPausedTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Level Time")
	float LevelTimerTickDelay;
	
	FTimerHandle InitLevelTimerHandle;
	
	FTimerHandle LevelTimerHandle;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(blueprintCallable)
	virtual void StartLevelTimer();
	
	UFUNCTION(blueprintCallable)
	virtual void ResumeLevelTimer();
	
	UFUNCTION(blueprintCallable)
	virtual void PauseLevelTimer();
	
	virtual void EndLevelTimer();
	
	UFUNCTION()
	virtual void LevelTimerTick();
	
};
