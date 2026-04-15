// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TS_SaveSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_SaveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(blueprintCallable)
	void SaveGeneralData();

	UFUNCTION(blueprintCallable)
	void SaveSlotData(const int32 SlotIndex);

	UFUNCTION(blueprintCallable)
	void LoadGeneralData();

	UFUNCTION(blueprintCallable)
	void LoadSlotData(const int32 SlotIndex);

	UFUNCTION(blueprintCallable)
	void SaveAllData(const int32 SlotIndex);
	
	UFUNCTION(BlueprintCallable)
	void DeleteGeneralData();
	
	UFUNCTION(BlueprintCallable)
	void DeleteSlotData(const int32 SlotIndex);
};
