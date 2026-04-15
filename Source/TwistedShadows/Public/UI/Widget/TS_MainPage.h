// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "UI/Widget/TS_Widget.h"
#include "TS_MainPage.generated.h"

class UTS_Button;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_MainPage : public UTS_Widget
{
	GENERATED_BODY()
	
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<UTS_Button> StartButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<UTS_Button> ContinueButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<UTS_Button> OptionButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (BindWidget), Category = "Buttons")
	TObjectPtr<UTS_Button> ExitButton;
	
	virtual void NativeConstruct() override;

	UFUNCTION()
	void OnStartButtonClicked(const FName ButtonId);
	
	UFUNCTION()
	void OnContinueButtonClicked(const FName ButtonId);

	UFUNCTION()
	void OnOptionButtonClicked(const FName ButtonId);

	UFUNCTION()
	void OnExitButtonClicked(const FName ButtonId);
};
