// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Save/TS_GlobalSaveGame.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TS_SaveSubsystem.generated.h"


class ITS_Savable;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGlobalSaveDataSignature, const UTS_GlobalSaveGame*, GlobalSave);

/**
 * @class UTS_SaveSubsystem
 * @brief A subsystem for handling save and load operations in the game.
 *
 * This class provides functionality to save and load both general data and slot-specific data.
 * It interacts with the game's save system to retain or fetch persistent data across sessions.
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
	void SaveData();
	
	UFUNCTION(BlueprintCallable)
	void DeleteGeneralData();
	
	UFUNCTION(BlueprintCallable)
	void DeleteSlotData(const int32 SlotIndex);
	
	UPROPERTY(blueprintAssignable)
	FGlobalSaveDataSignature OnGlobalSaveDataDelegate;

	UFUNCTION(BlueprintCallable)
	UTS_GlobalSaveGame* GetGlobalSaveGame() const { return GlobalSaveGame; }
	
	FString GlobalDataName = TEXT("GlobalData");
	
	UFUNCTION()
	void CreateGlobalSaveGame();

	UFUNCTION(BlueprintCallable)
	void RegisterObject(const TScriptInterface<ITS_Savable> Savable);
	
	UFUNCTION(BlueprintCallable)
	void UnregisterObject(const TScriptInterface<ITS_Savable> Savable);
	
protected:
	
	UPROPERTY()
	UTS_GlobalSaveGame* GlobalSaveGame;
	
	UFUNCTION()
	void OnGeneralDataLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSave);

	UPROPERTY(BlueprintReadOnly)
	TArray<TScriptInterface<ITS_Savable>> SlotRegistry;
	
};
