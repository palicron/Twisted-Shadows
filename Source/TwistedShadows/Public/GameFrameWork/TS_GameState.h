// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TS_GameState.generated.h"

class UMVVM_LevelFlow;
class UTS_Widget;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_GameState : public AGameState
{
	GENERATED_BODY()
	
public:
	
	ATS_GameState();
	
	UFUNCTION(BlueprintCallable)
	UMVVM_LevelFlow* GetLevelFlowViewModel() const { return LevelFlowViewModel; }
	
protected:
	
	float StartDelayTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Level Time")
	float LevelInitialTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "Level Time")
	float LevelTimerTickDelay;
	
	float LevelEndTime;
	
	float LevelTimer;
	
	float PauseStartTime;
	
	float TotalPausedTime;
	
	FTimerHandle InitLevelTimerHandle;
	
	FTimerHandle LevelTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category= "UI | View Model")
	TSubclassOf<UMVVM_LevelFlow> LevelFlowViewModelClass;
	
	UPROPERTY()
	TObjectPtr<UMVVM_LevelFlow> LevelFlowViewModel;
	
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
