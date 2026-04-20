// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TS_GlobalSaveGame.generated.h"

class UTS_SlotSaveGame;

USTRUCT(BlueprintType)
struct FLevelPreviewInfo
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SlotProgress;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NextLevelIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FText NextLevelName;
	
};
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API UTS_GlobalSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere)
	int32 LastUsedSlotIndex;
	
	UPROPERTY(VisibleAnywhere)
	TMap<int32, FLevelPreviewInfo> SlotSummaries;
	
	UPROPERTY(VisibleAnywhere)
	FString CurrentLanguage = "en";
	
	UTS_GlobalSaveGame();
	
	
};
