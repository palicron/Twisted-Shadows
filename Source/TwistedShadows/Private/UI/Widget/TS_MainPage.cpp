// Twisted Shadow make by JSP


#include "UI/Widget/TS_MainPage.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/TS_LevelFlowSubsystem.h"
#include "UI/Widget/TS_Button.h"
void UTS_MainPage::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartButton)
	{
		StartButton->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_MainPage::OnStartButtonClicked);
	}
	if (ContinueButton)
	{
		ContinueButton->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_MainPage::OnContinueButtonClicked);
	}
	if (OptionButton)
	{
		OptionButton->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_MainPage::OnOptionButtonClicked);
	}
	if (ExitButton)
	{
		ExitButton->OnButtonBaseClickedDelegate.AddDynamic(this, &UTS_MainPage::OnExitButtonClicked);
	}
}

void UTS_MainPage::OnStartButtonClicked(const FName ButtonId)
{
	//TODO for the momen this will start the fdirt level ,
	//THis should open the slot sreacha nd there the flow shoudl continue
	
	UTS_LevelFlowSubsystem* FlowSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_LevelFlowSubsystem>();
	FlowSubsystem->StartNewGame(0);
	
}

void UTS_MainPage::OnContinueButtonClicked(const FName ButtonId)
{
	//TODO For the moment i only will be using the slot 0 Need to implement UI for the others
	UTS_LevelFlowSubsystem* FlowSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_LevelFlowSubsystem>();
	FlowSubsystem->ContinueGame();
}

void UTS_MainPage::OnOptionButtonClicked(const FName ButtonId)
{
	//TODO Shoudl open a option pannel 
	//Pro y whant to make some input biding  adn languaje changes
}

void UTS_MainPage::OnExitButtonClicked(const FName ButtonId)
{
	//Need to save game and Delay Exit fo rthe moment only quit
	
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(this, 0), EQuitPreference::Quit, false);
}
