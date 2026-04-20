// Twisted Shadow make by JSP


#include "Subsystems/TS_SaveSubsystem.h"

#include "Functions/TSStatics.h"
#include "Interfaces/TS_Savable.h"
#include "Kismet/GameplayStatics.h"
#include "Save/TS_SlotSaveGame.h"
#include "Subsystems/TS_LevelFlowSubsystem.h"

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
	for (int32 i = 0; i < MaxSaveSlots; i++)
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
			UGameplayStatics::SaveGameToSlot(SlotSave, SlotName, 0);
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

	//TODO NO CALL THOS
	for (TScriptInterface<ITS_Savable> Savable : SlotRegistry)
	{
		ITS_Savable::Execute_OnSlotSave(Savable.GetObject(), NewSave);
	}

	FString SlotName = FString::Printf(TEXT("Slot_%d"), CurrentSaveIndex);
	UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);
	
	UTS_LevelFlowSubsystem* LevelFlow = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UTS_LevelFlowSubsystem>();
	FLevelProgress Progression =  UTSStatics::GetCurrentLevelProgress(this);

	//TODO NEED TO FIN THE NEXT LEVLE NAME 
	//TODO NEED TO SE PROGRESSIOn
	if (GlobalSaveGame->SlotSummaries.Contains(CurrentSaveIndex))
	{
		GlobalSaveGame->SlotSummaries[CurrentSaveIndex].NextLevelIndex = Progression.NextLevelID;
	}
	else
	{
		FLevelPreviewInfo NewPreview;
		NewPreview.NextLevelIndex = Progression.NextLevelID;
	
		//TODO CHECK CORREC INDEX
		GlobalSaveGame->SlotSummaries.Add(0,NewPreview);
	}
	
	
	SaveGeneralData();
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

const UTS_SlotSaveGame* UTS_SaveSubsystem::GetCurrentSlotSaveGame() const
{
	return GetSlotSaveGame(CurrentSaveIndex);
}

void UTS_SaveSubsystem::InitNewSlotGame(const int32 SlotIndex)
{
	UTS_SlotSaveGame* NewSave = GetSlotSaveGame(SlotIndex);

	if (!NewSave)
	{
		return;
	}

	NewSave->bStartedGame = true;

	FString SlotName = FString::Printf(TEXT("Slot_%d"), SlotIndex);
	UGameplayStatics::SaveGameToSlot(NewSave, SlotName, 0);
}
