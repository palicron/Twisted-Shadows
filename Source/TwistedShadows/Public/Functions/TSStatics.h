// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions/GeneralDefinitions.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSStatics.generated.h"

class UMVVM_LevelFlow;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTSStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static UMVVM_LevelFlow* GetLevelFlowViewModel(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintPure)
	static FText GetLevelTimeInTextFormat(const float TimeInSec);
	
	UFUNCTION(BlueprintPure, meta = (WorldContext = "WorldContextObject"))
	static FLevelProgress GetCurrentLevelProgress(const UObject* WorldContextObject);
	
};
