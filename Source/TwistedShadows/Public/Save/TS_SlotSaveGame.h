// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TS_SlotSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FLevelData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BestTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HighScore;
	
	FLevelData() : LevelID(0), BestTime(FLT_MAX), HighScore(0)
	{
	};
};

/**
 * @class UTS_SlotSaveGame
 * @brief A class for managing and storing save game data specific to the Twisted Shadows game.
 *
 * This class extends the USaveGame base class and serves as a container for persistent game state data.
 * It is designed to store information such as the timestamp of the save and detailed data about the levels.
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_SlotSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDateTime SaveTimestamp;

	UPROPERTY(VisibleAnywhere)
	TMap<int32, FLevelData> LevelData;
};
