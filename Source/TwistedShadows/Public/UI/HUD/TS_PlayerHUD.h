// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TS_PlayerHUD.generated.h"

class UTS_EndLevelWidget;
class UTS_Widget;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_PlayerHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	UTS_Widget* GetPlayerHUDWidget() const { return PlayerHUDWidget;};
	
	UFUNCTION(BlueprintCallable)
	void DisplayEndLevelWidget();
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget")
	TSubclassOf<UTS_Widget> PlayerHUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTS_Widget> PlayerHUDWidget;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget")
	TSubclassOf<UTS_EndLevelWidget> EndLevelWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTS_EndLevelWidget> EndLevelWidget;
	
	virtual void BeginPlay() override;
};
