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


