// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/WorldSettings.h"
#include "TS_WorldSettings.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TWISTEDSHADOWS_API ATS_WorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bIsMenu : 1;
	
	ATS_WorldSettings();
	
	
};
