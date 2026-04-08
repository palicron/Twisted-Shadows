// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/TS_LevelFlowSubsystem.h"

void UTS_LevelFlowSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
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
