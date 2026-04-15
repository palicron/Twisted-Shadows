// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Definitions/GeneralDefinitions.h"
#include "Engine/DataAsset.h"
#include "TS_LevelDefinitionDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_LevelDefinitionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	int32 StartingLevelIndex = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 MainMenuLevelIndex = 0;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FLevelDefinition> LevelDefinitions;
};
