// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TS_PlayerHUD.h"

#include "UI/Widget/TS_EndLevelWidget.h"
#include "UI/Widget/TS_Widget.h"

void ATS_PlayerHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(PlayerHUDWidgetClass))
	{
		PlayerHUDWidget = CreateWidget<UTS_Widget>(GetWorld(), PlayerHUDWidgetClass);
		PlayerHUDWidget->AddToViewport();
	}
}

void ATS_PlayerHUD::DisplayEndLevelWidget()
{
	if (!IsValid(EndLevelWidgetClass))
	{
		return;
	}

	EndLevelWidget = CreateWidget<UTS_EndLevelWidget>(GetWorld(), EndLevelWidgetClass);
	EndLevelWidget->SetPositionInViewport(FVector2D(0, 0));
	EndLevelWidget->SetAnchorsInViewport(FAnchors(0.5f, 0.5f));
	EndLevelWidget->SetAlignmentInViewport(FVector2D(0.5f, 0.5f));
	EndLevelWidget->AddToViewport();
	if (PlayerHUDWidget)
	{
		PlayerHUDWidget->RemoveFromParent();
	}
	

}
