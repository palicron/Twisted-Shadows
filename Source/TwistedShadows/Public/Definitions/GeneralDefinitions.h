#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GeneralDefinitions.generated.h"

UENUM(BlueprintType)
enum class ETS_ActivationState : uint8
{
	None,
	Activated,
	Activating,
	Deactivating,
	Deactivated,
	Disabled
};

USTRUCT(BlueprintType)
struct FActivationPayload
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	FGameplayTagContainer ActivationTags;
	
	UPROPERTY(BlueprintReadOnly)
	float ActivationTime;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AActor> InstigatorActivator;
	
	UPROPERTY(BlueprintReadOnly)
	TWeakObjectPtr<AActor> Instigator;
	
};

USTRUCT(BlueprintType)
struct FLevelDefinition 
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText LevelName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText LevelDescription;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> LevelAsset; 
};

USTRUCT(BlueprintType)
struct FLevelProgress       
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 LevelID;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText LevelName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText LevelDescription;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UWorld> LevelAsset; 
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	uint8 bIsAlreadyFinish : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BestFinishTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float LastFinishTime;
	
	int32 LevelHighScore;


	FLevelProgress() : LevelID(0), bIsAlreadyFinish(false), BestFinishTime(0.f), LastFinishTime(0.f), LevelHighScore(0.f)
	{
	};
};



