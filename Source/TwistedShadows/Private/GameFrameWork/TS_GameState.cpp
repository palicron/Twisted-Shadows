// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFrameWork/TS_GameState.h"

#include "UI/ViewModel/MVVM_LevelFlow.h"

ATS_GameState::ATS_GameState()
{
	StartDelayTime = 3.f;
	LevelTimerTickDelay = 1.f;
	LevelTimer = 0.f;
	PauseStartTime = 0.f;
	TotalPausedTime = 0.f;
	LevelEndTime = 0.f;
}

void ATS_GameState::BeginPlay()
{
	Super::BeginPlay();
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(InitLevelTimerHandle,this,&ATS_GameState::StartLevelTimer,StartDelayTime,false);
	}
	
	if (IsValid(LevelFlowViewModelClass))
	{
		LevelFlowViewModel = NewObject<UMVVM_LevelFlow>(this, LevelFlowViewModelClass);
		LevelFlowViewModel->SetLevelTimeInSeconds(0.f);
	}
}

void ATS_GameState::StartLevelTimer()
{
	if (!GetWorld())
	{
		return;
	}
	LevelInitialTime = GetWorld()->GetTimeSeconds();
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle,this,&ATS_GameState::LevelTimerTick,LevelTimerTickDelay,{true,true});
}

void ATS_GameState::ResumeLevelTimer()
{
	if (!GetWorld())
	{
		return;
	}

	TotalPausedTime += GetWorld()->GetTimeSeconds() - PauseStartTime;
	GetWorld()->GetTimerManager().SetTimer(LevelTimerHandle, this, &ATS_GameState::LevelTimerTick, LevelTimerTickDelay, {true, true});
}

void ATS_GameState::PauseLevelTimer()
{
	PauseStartTime = GetWorld()->GetTimeSeconds();
	GetWorld()->GetTimerManager().ClearTimer(LevelTimerHandle);
}

void ATS_GameState::EndLevelTimer()
{
	LevelEndTime = GetWorld()->GetTimeSeconds() - LevelInitialTime;
	GetWorld()->GetTimerManager().ClearTimer(LevelTimerHandle);
}

void ATS_GameState::LevelTimerTick()
{
	LevelTimer = GetWorld()->GetTimeSeconds() - LevelInitialTime - TotalPausedTime;
	
	if (LevelFlowViewModel)
	{
		LevelFlowViewModel->SetLevelTimeInSeconds(LevelTimer);
	}

}
