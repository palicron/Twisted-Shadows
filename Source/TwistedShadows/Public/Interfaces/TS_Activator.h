// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/Activator/TS_ActivatorComponent.h"
#include "UObject/Interface.h"
#include "TS_Activator.generated.h"

class ITS_Activatable;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTS_Activator : public UInterface
{
	GENERATED_BODY()
};

/**
 * @class ITS_Activator
 * @brief Interface for managing activatable actors in the system.
 *
 * This interface defines the functions required to retrieve, activate, and deactivate
 * a collection of actors that implement the ITS_Activatable interface.
 */
class TWISTEDSHADOWS_API ITS_Activator
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsActivatableActorEnabled() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTS_ActivatorComponent* GetActivatorComponent() const;
};
	