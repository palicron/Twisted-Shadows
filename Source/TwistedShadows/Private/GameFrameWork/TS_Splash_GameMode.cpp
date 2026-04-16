// Twisted Shadow make by JSP


#include "GameFrameWork/TS_Splash_GameMode.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/TS_LevelFlowSubsystem.h"
#include "Subsystems/TS_SaveSubsystem.h"

void ATS_Splash_GameMode::BeginPlay()
{
	Super::BeginPlay();

	FlowSubsystemPtr = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_LevelFlowSubsystem>();
	SaveSubsystemPtr = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_SaveSubsystem>();
	
	if (SaveSubsystemPtr.IsValid())
	{
		if (UTS_GlobalSaveGame* GlobalSave = SaveSubsystemPtr->GetGlobalSaveGame())
		{
			AdvanceToMenuLevel();
			return;
		}
		else
		{
			SaveSubsystemPtr->OnGlobalSaveDataDelegate.AddDynamic(this,&ATS_Splash_GameMode::OnGlobalSaveDataCallBack);
			SaveSubsystemPtr->CreateGlobalSaveGame();
		}
	}
}

void ATS_Splash_GameMode::AdvanceToMenuLevel()
{
	if (FlowSubsystemPtr.IsValid())
	{
		FlowSubsystemPtr->LoadMainMenu();
	}
}

void ATS_Splash_GameMode::OnGlobalSaveDataCallBack(const UTS_GlobalSaveGame* GlobalSave)
{
	AdvanceToMenuLevel();
}
