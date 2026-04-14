// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TS_MenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_MenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;
	
};
