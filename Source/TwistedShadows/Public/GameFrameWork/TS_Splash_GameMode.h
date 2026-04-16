// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFrameWork/TS_GameMode_Base.h"
#include "TS_Splash_GameMode.generated.h"

class UTS_GlobalSaveGame;
class UTS_SaveSubsystem;
class UTS_LevelFlowSubsystem;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_Splash_GameMode : public ATS_GameMode_Base
{
	GENERATED_BODY()
	
protected:
	
	TWeakObjectPtr<UTS_LevelFlowSubsystem> FlowSubsystemPtr;
	TWeakObjectPtr<UTS_SaveSubsystem> SaveSubsystemPtr;
	
	virtual void BeginPlay() override;
	
	void AdvanceToMenuLevel();
	
	UFUNCTION()
	void OnGlobalSaveDataCallBack(const UTS_GlobalSaveGame* GlobalSave);
};
