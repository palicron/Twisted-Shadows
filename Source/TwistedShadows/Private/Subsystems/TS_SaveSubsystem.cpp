// Twisted Shadow make by JSP


#include "Subsystems/TS_SaveSubsystem.h"

#include "Interfaces/TS_Savable.h"
#include "Kismet/GameplayStatics.h"
#include "Save/TS_SlotSaveGame.h"

void UTS_SaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	CurrentSaveIndex = 0;
}

void UTS_SaveSubsystem::SaveGeneralData()
{
	if (!UGameplayStatics::DoesSaveGameExist(GlobalDataName, 0))
	{
		return;
	}

	UGameplayStatics::SaveGameToSlot(GlobalSaveGame, GlobalDataName, 0);
}

void UTS_SaveSubsystem::LoadGeneralData()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUFunction(this, "OnGeneralDataLoad");

	UGameplayStatics::AsyncLoadGameFromSlot(GlobalDataName, 0, LoadedDelegate);
}

void UTS_SaveSubsystem::LoadData()
{
	for (int32 i = 0; i < SlotSaveGames.Num(); i++)
	{
		FString SlotName = FString::Printf(TEXT("Slot_%d"), i);
		if (UTS_SlotSaveGame* NewSave = Cast<UTS_SlotSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
		{
			SlotSaveGames.Add(NewSave);
		}
		else
		{
			UTS_SlotSaveGame* SlotSave = NewObject<UTS_SlotSaveGame>();
			SlotSaveGames.Add(SlotSave);
		}
	}
}

void UTS_SaveSubsystem::SaveData()
{
	UTS_SlotSaveGame* NewSave = GetSlotSaveGame(CurrentSaveIndex);

	if (!NewSave)
	{
		return;
	}

	for (TScriptInterface<ITS_Savable> Savable : SlotRegistry)
	{
		Savable->OnSlotSave(NewSave);
	}

	FString SlotName = FString::Printf(TEXT("Slot_%d"), CurrentSaveIndex);
	UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);
}

void UTS_SaveSubsystem::DeleteGeneralData()
{
}

void UTS_SaveSubsystem::DeleteSlotData(const int32 SlotIndex)
{
}

void UTS_SaveSubsystem::OnGeneralDataLoad(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedSave)
{
	if (LoadedSave)
	{
		GlobalSaveGame = Cast<UTS_GlobalSaveGame>(LoadedSave);
		if (GlobalSaveGame)
		{
			OnGlobalSaveDataDelegate.Broadcast(GlobalSaveGame);
		}
	}
	else
	{
		CreateGlobalSaveGame();
	}
}

void UTS_SaveSubsystem::CreateGlobalSaveGame()
{
	if (UGameplayStatics::DoesSaveGameExist(GlobalDataName, 0))
	{
		LoadGeneralData();
		return;
	}

	if (UTS_GlobalSaveGame* NewGlobal = Cast<UTS_GlobalSaveGame>(UGameplayStatics::CreateSaveGameObject(UTS_GlobalSaveGame::StaticClass())))
	{
		GlobalSaveGame = NewGlobal;
		UGameplayStatics::SaveGameToSlot(NewGlobal, GlobalDataName, 0);
		OnGlobalSaveDataDelegate.Broadcast(GlobalSaveGame);
	}
}

void UTS_SaveSubsystem::RegisterObject(const TScriptInterface<ITS_Savable> Savable)
{
	if (!Savable)
	{
		return;
	}
	
	SlotRegistry.Add(Savable);
}

void UTS_SaveSubsystem::UnregisterObject(const TScriptInterface<ITS_Savable> Savable)
{
	if (!Savable)
	{
		return;
	}
	
	SlotRegistry.Remove(Savable);
}

UTS_SlotSaveGame* UTS_SaveSubsystem::GetSlotSaveGame(const int32 SlotIndex) const
{
	if (SlotIndex >= SlotSaveGames.Num() - 1)
	{
		return nullptr;
	}

	return SlotSaveGames[SlotIndex];
}
