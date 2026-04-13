// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/TS_Widget.h"
#include "TS_EndLevelWidget.generated.h"

class UTS_LevelFlowSubsystem;
class UTS_Button;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_EndLevelWidget : public UTS_Widget
{
	GENERATED_BODY()
	
	
protected:
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTS_Button> Button_Reset;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTS_Button> Button_Next;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<UTS_Button> Button_Menu;
	
	TWeakObjectPtr<UTS_LevelFlowSubsystem> FlowSubsystem;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnNextButtonClicked(const FName ButtonId);
	
	UFUNCTION()
	void OnResetButtonClicked(const FName ButtonId);
	
	UFUNCTION()
	void OnMainMenutButtonClicked(const FName ButtonId);
	
	
};
