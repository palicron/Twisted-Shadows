// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/TS_GameMode_Base.h"
#include "TS_Menu_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_Menu_GameMode : public ATS_GameMode_Base
{
	GENERATED_BODY()
	
	
protected:
	
	virtual void BeginPlay() override;
	
};
