// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TS_PlayerHUD.h"

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
