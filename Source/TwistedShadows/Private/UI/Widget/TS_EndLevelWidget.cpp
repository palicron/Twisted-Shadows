// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TS_EndLevelWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/TS_LevelFlowSubsystem.h"
#include "UI/Widget/TS_Button.h"

void UTS_EndLevelWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FlowSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_LevelFlowSubsystem>();

	if (Button_Next)
	{
		Button_Next->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_EndLevelWidget::OnNextButtonClicked);
	}

	if (Button_Reset)
	{
		Button_Reset->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_EndLevelWidget::OnResetButtonClicked);
	}

	if (Button_Menu)
	{
		Button_Menu->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_EndLevelWidget::OnMainMenutButtonClicked);
	}
	
	//TODO NEED TO CHECK FOR NEXT LEVEL IF NOT VLAID DISALBE BUTTON ONLY SHOW RESET AND MAIN MENu
}

void UTS_EndLevelWidget::OnNextButtonClicked(const FName ButtonId)
{
	if (!FlowSubsystem.IsValid())
	{
		return;
	}

	FlowSubsystem->LoadNextLevel();
}

void UTS_EndLevelWidget::OnResetButtonClicked(const FName ButtonId)
{
	if (!FlowSubsystem.IsValid())
	{
		return;
	}

	FlowSubsystem->ReloadLevel();
}

void UTS_EndLevelWidget::OnMainMenutButtonClicked(const FName ButtonId)
{
	FlowSubsystem->LoadMainMenu();
}
