// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/TS_Widget.h"
#include "TS_Button.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnButtonBaseClickedSignature, FName, ButtonID);
/**
 * TS Generic button
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_Button : public UTS_Widget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonBaseClickedSignature OnButtonBaseClickedDelegate;
	
	UFUNCTION(BlueprintCallable)
	FText GetButtonLabel() const { return ButtonLabel; }
	
	UFUNCTION(BlueprintCallable)
	void SetButtonLabel(FText InButtonLabel);
	
	UFUNCTION(BlueprintCallable)
	FName GetButtonID() const { return ButtonID; }
	
	UFUNCTION(BlueprintCallable)
	void SetButtonID(const FName InButtonID) { ButtonID = InButtonID;};
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Button")
	float OverrideWidth = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Button")
	float OverrideHeight = 10.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Button")
	FText ButtonLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Button")
	FName ButtonID;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UButton> Button;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class USizeBox> SizeBox_Root;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Text_Label;
	
	virtual void NativePreConstruct() override;
	
	virtual void NativeConstruct() override;
	
	UFUNCTION()
	void OnButtonClicked();
};
