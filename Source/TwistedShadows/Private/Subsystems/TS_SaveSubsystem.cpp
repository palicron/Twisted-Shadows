// Twisted Shadow make by JSP


#include "Subsystems/TS_SaveSubsystem.h"

#include "Kismet/GameplayStatics.h"

void UTS_SaveSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
}

void UTS_SaveSubsystem::SaveGeneralData()
{
	if (!UGameplayStatics::DoesSaveGameExist(GlobalDataName, 0))
	{
		return;
	}

	UGameplayStatics::SaveGameToSlot(GlobalSaveGame, GlobalDataName, 0);
}

void UTS_SaveSubsystem::SaveSlotData(const int32 SlotIndex)
{
	FString SlotName = FString::Printf(TEXT("Slot_%d"), SlotIndex);
	
}

void UTS_SaveSubsystem::LoadGeneralData()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUFunction(this, "OnGeneralDataLoad");

	UGameplayStatics::AsyncLoadGameFromSlot(GlobalDataName, 0, LoadedDelegate);
}

void UTS_SaveSubsystem::LoadSlotData(const int32 SlotIndex)
{
}

void UTS_SaveSubsystem::SaveAllData(const int32 SlotIndex)
{
	
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
