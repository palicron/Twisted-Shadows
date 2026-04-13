// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/TS_Button.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UTS_Button::SetButtonLabel(FText InButtonLabel)
{
}

void UTS_Button::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	if (Text_Label)
	{
		Text_Label->SetText(ButtonLabel);
	}
	
	if (SizeBox_Root)
	{
		SizeBox_Root->SetWidthOverride(OverrideWidth);
		SizeBox_Root->SetHeightOverride(OverrideHeight);
	}

}

void UTS_Button::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Text_Label)
	{
		Text_Label->SetText(ButtonLabel);
	}
	
	if (Button)
	{
		Button->OnClicked.AddDynamic(this, &UTS_Button::OnButtonClicked);
	}
}

void UTS_Button::OnButtonClicked()
{
	OnButtonBaseClickedDelegate.Broadcast(ButtonID);
}
