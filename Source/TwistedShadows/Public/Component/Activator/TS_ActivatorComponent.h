// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Definitions/GeneralDefinitions.h"
#include "TS_ActivatorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActivationStateChangedSignature, const FActivationPayload&, Payload);
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWISTEDSHADOWS_API UTS_ActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTS_ActivatorComponent();

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
	TArray<FGameplayTag> ActivationTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation")
	TArray<FGameplayTag> DeactivationTags;

public:	
	
	UPROPERTY(BlueprintAssignable)
	FOnActivationStateChangedSignature OnActivationDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnActivationStateChangedSignature OnDeactivationDelegate;
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateActors(AActor* Instigator = nullptr);

	UFUNCTION(BlueprintCallable)
	virtual void DeActivateActors(AActor* Instigator = nullptr);
};
