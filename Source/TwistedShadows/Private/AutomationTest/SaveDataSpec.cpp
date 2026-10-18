// Twisted Shadow make by JSP

#include "Misc/AutomationTest.h"
#include "Engine/GameInstance.h"
#include "Save/TS_GlobalSaveGame.h"
#include "Save/TS_SlotSaveGame.h"
#include "Subsystems/TS_SaveSubsystem.h"

#if WITH_DEV_AUTOMATION_TESTS

/**
 * Unit tests for the save data types and UTS_SaveSubsystem lookups.
 * Nothing here writes to disk: LoadData / SaveData / SaveGameToSlot are never called.
 */
BEGIN_DEFINE_SPEC(FTSSaveDataSpec, "TwistedShadows.Unit.SaveData",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

	TObjectPtr<UGameInstance> GameInstance;
	TObjectPtr<UTS_SaveSubsystem> SaveSubsystem;

	/** SlotSaveGames is protected; reach it through reflection so the subsystem needs no test hooks. */
	TArray<UTS_SlotSaveGame*>* GetSlotArray()
	{
		const FArrayProperty* Property = FindFProperty<FArrayProperty>(UTS_SaveSubsystem::StaticClass(), TEXT("SlotSaveGames"));
		if (!Property)
		{
			AddError(TEXT("UTS_SaveSubsystem::SlotSaveGames property not found"));
			return nullptr;
		}
		return Property->ContainerPtrToValuePtr<TArray<UTS_SlotSaveGame*>>(SaveSubsystem.Get());
	}

	TArray<UTS_SlotSaveGame*> FillSlots(const int32 Count)
	{
		TArray<UTS_SlotSaveGame*> Created;
		TArray<UTS_SlotSaveGame*>* Slots = GetSlotArray();
		if (!Slots)
		{
			return Created;
		}
		for (int32 i = 0; i < Count; i++)
		{
			UTS_SlotSaveGame* Slot = NewObject<UTS_SlotSaveGame>(GetTransientPackage());
			Slots->Add(Slot);
			Created.Add(Slot);
		}
		return Created;
	}

END_DEFINE_SPEC(FTSSaveDataSpec)

void FTSSaveDataSpec::Define()
{
	Describe("Default values", [this]()
	{
		It("FLevelData starts with BestTime = FLT_MAX so any finish time is better", [this]()
		{
			const FLevelData Data;
			TestEqual(TEXT("LevelID"), Data.LevelID, 0);
			TestEqual(TEXT("BestTime"), Data.BestTime, FLT_MAX);
			TestEqual(TEXT("HighScore"), Data.HighScore, 0);
		});

		It("UTS_SlotSaveGame starts not started and with no level data", [this]()
		{
			const UTS_SlotSaveGame* Save = NewObject<UTS_SlotSaveGame>(GetTransientPackage());
			TestFalse(TEXT("bStartedGame"), static_cast<bool>(Save->bStartedGame));
			TestEqual(TEXT("LevelData entries"), Save->LevelData.Num(), 0);
		});

		It("UTS_GlobalSaveGame starts with no used slot and English", [this]()
		{
			const UTS_GlobalSaveGame* Save = NewObject<UTS_GlobalSaveGame>(GetTransientPackage());
			TestEqual(TEXT("LastUsedSlotIndex"), Save->LastUsedSlotIndex, -1);
			TestEqual(TEXT("CurrentLanguage"), Save->CurrentLanguage, FString(TEXT("en")));
			TestEqual(TEXT("SlotSummaries entries"), Save->SlotSummaries.Num(), 0);
		});
	});

	Describe("UTS_SaveSubsystem::GetSlotSaveGame", [this]()
	{
		BeforeEach([this]()
		{
			// UGameInstanceSubsystem is Within=GameInstance, so the outer must be a game instance. It is not initialized.
			GameInstance = NewObject<UGameInstance>(GetTransientPackage());
			SaveSubsystem = NewObject<UTS_SaveSubsystem>(GameInstance);
		});

		AfterEach([this]()
		{
			SaveSubsystem = nullptr;
			GameInstance = nullptr;
		});

		It("returns nullptr when no slots are loaded", [this]()
		{
			TestNull(TEXT("Slot 0"), SaveSubsystem->GetSlotSaveGame(0));
		});

		It("returns the first and middle slots", [this]()
		{
			const TArray<UTS_SlotSaveGame*> Slots = FillSlots(3);
			if (Slots.Num() != 3) { return; }

			TestTrue(TEXT("Slot 0"), SaveSubsystem->GetSlotSaveGame(0) == Slots[0]);
			TestTrue(TEXT("Slot 1"), SaveSubsystem->GetSlotSaveGame(1) == Slots[1]);
		});

		It("returns the last slot", [this]()
		{
			const TArray<UTS_SlotSaveGame*> Slots = FillSlots(3);
			if (Slots.Num() != 3) { return; }

			TestTrue(TEXT("Slot 2 of 3"), SaveSubsystem->GetSlotSaveGame(2) == Slots[2]);
		});

		It("returns nullptr past the last slot", [this]()
		{
			FillSlots(3);
			TestNull(TEXT("Slot 3 of 3"), SaveSubsystem->GetSlotSaveGame(3));
		});

		It("returns the only slot when one slot is loaded", [this]()
		{
			const TArray<UTS_SlotSaveGame*> Slots = FillSlots(1);
			if (Slots.Num() != 1) { return; }

			TestTrue(TEXT("Slot 0 of 1"), SaveSubsystem->GetSlotSaveGame(0) == Slots[0]);
		});
	});
}

#endif
