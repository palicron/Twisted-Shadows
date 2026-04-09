// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TS_GameInstance.generated.h"

class UTS_LevelDefinitionDataAsset;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTS_LevelDefinitionDataAsset> LevelDefinitions;
	
};
