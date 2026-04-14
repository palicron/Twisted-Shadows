// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/TS_MenuHUD.h"

#include "Engine/Canvas.h"
#include "UI/Widget/TS_MainMenuWidget.h"

void ATS_MenuHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(MainMenuWidgetClass))
	{
		MainMenuWidget = CreateWidget<UTS_MainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		MainMenuWidget->AddToViewport();
	}
}

void ATS_MenuHUD::DrawHUD()
{
	Super::DrawHUD();

	const FString Name = FApp::GetProjectName();
	const FString Version = FApp::GetBuildVersion();
	FString Build;
	GConfig->GetString(
		TEXT("/Script/EngineSettings.GeneralProjectSettings"),
		TEXT("ProjectVersion"),
		Build,
		GGameIni
	);
	
	const float BuildPosY = Canvas->SizeY - 35.f;
	const float NamePosY = Canvas->SizeY - 35.f;
	const float VersionPosY = Canvas->SizeY - 20.f;

	const float PosX = 10.f;
	const float VPosX = 120.f;
	DrawText(
		Name,
		FLinearColor::White,
		PosX,
		NamePosY,
		GEngine->GetSmallFont(),
		1.f
	);

	DrawText(
		Version,
		FLinearColor::White,
		PosX,
		VersionPosY,
		GEngine->GetSmallFont(),
		1.f
	);

	DrawText(
		"V " + Build,
		FLinearColor::White,
		VPosX,
		BuildPosY,
		GEngine->GetSmallFont(),
		1.f
	);
}
