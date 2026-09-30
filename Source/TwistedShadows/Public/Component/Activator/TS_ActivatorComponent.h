// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Definitions/GeneralDefinitions.h"
#include "TS_ActivatorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivationStateChangedSignature, FActivationPayload, Payload);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWISTEDSHADOWS_API UTS_ActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTS_ActivatorComponent();

public:
	UPROPERTY(BlueprintAssignable, meta = (ActivationEvent))
	FOnActivationStateChangedSignature OnActivationDelegate;

	UFUNCTION(BlueprintCallable)
	virtual void ActivateActors(const FGameplayTagContainer ActivationTags , AActor* Instigator = nullptr);
};
