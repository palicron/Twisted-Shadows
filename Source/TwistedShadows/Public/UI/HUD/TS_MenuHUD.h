// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TS_MenuHUD.generated.h"

class UTS_MainMenuWidget;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_MenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widget")
	TSubclassOf<UTS_MainMenuWidget> MainMenuWidgetClass;

	UPROPERTY()
	TObjectPtr<UTS_MainMenuWidget> MainMenuWidget;

	virtual void BeginPlay() override;
	
	virtual void DrawHUD() override;
	
	
};
