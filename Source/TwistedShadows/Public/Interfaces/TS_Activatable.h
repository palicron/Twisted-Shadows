// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Definitions/GeneralDefinitions.h"
#include "UObject/Interface.h"
#include "TS_Activatable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTS_Activatable : public UInterface
{
	GENERATED_BODY()
};

/**
 * @brief Interface to enable actors to support activation and deactivation behavior.
 *
 * This class defines a set of functions that can be implemented to control the activation
 * lifecycle of an actor. Actors implementing this interface can be activated, deactivated,
 * queried for their activation phase, and queried for their current activation state.
 */
class TWISTEDSHADOWS_API ITS_Activatable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, blueprintCallable)
	void ActivateActor();

	UFUNCTION(BlueprintNativeEvent, blueprintCallable)
	void DeactivateActor();

	UFUNCTION(BlueprintNativeEvent, blueprintCallable)
	int32 GetActivationPhase() const;

	UFUNCTION(BlueprintNativeEvent, blueprintCallable)
	ETS_ActivationState GetActivationState() const;
};
