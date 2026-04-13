// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TS_GameMode_Base.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_GameMode_Base : public AGameMode
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void EndLevel(ACharacter* EndPlayer);
	
};
