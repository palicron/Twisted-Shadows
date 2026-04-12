// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ViewModel/MVVM_LevelFlow.h"

#include "Functions/TSStatics.h"


void UMVVM_LevelFlow::SetLevelTimeText(const FText& InLevelTime)
{
	UE_MVVM_SET_PROPERTY_VALUE(LevelTimeText,InLevelTime);
}

void UMVVM_LevelFlow::SetLevelTimeInSeconds(float InLevelTimeInSeconds)
{
	UE_MVVM_SET_PROPERTY_VALUE(LevelTimeInSeconds, InLevelTimeInSeconds);

	SetLevelTimeText(UTSStatics::GetLevelTimeInTextFormat(InLevelTimeInSeconds));
}
