#pragma once

#include "CoreMinimal.h"
#include "GeneralDefinitions.generated.h"

UENUM(BlueprintType)
enum class ETS_ActivationState : uint8
{
	None,
	Activated,
	Deactivated,
	Disabled
};
