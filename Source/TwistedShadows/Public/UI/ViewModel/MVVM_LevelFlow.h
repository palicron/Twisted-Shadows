// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LevelFlow.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UMVVM_LevelFlow : public UMVVMViewModelBase
{
	GENERATED_BODY()
	
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	FText LevelTimeText;
	
	void SetLevelTimeText(const FText& InLevelTime);
	
	FText GetLevelTimeText() const { return LevelTimeText; };
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter)
	float LevelTimeInSeconds;
	
	void SetLevelTimeInSeconds(float InLevelTimeInSeconds);
	
	float GetLevelTimeInSeconds() const { return LevelTimeInSeconds; };
	
};
