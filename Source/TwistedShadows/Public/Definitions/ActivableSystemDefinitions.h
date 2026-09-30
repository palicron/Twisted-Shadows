#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ActivableSystemDefinitions.generated.h"


USTRUCT(BlueprintType)
struct FActivationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	FGameplayTagContainer RequiredTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	FGameplayTagContainer RestrictTags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	uint8 bMatchAllTags : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	uint8 bMatchAllRestrictTags : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
	FName EventName;
};
