// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Definitions/GeneralDefinitions.h"
#include "Interfaces/TS_Activatable.h"
#include "TS_ActivatableComponent.generated.h"


class ITS_Activator;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWISTEDSHADOWS_API UTS_ActivatableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UTS_ActivatableComponent();
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateActor(FActivationPayload Payload);
	
	UFUNCTION(BlueprintCallable)
	virtual void DeactivateActor(FActivationPayload Payload);

protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	uint8 bCanBeActivate : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	TArray<FGameplayTag> RequiredTags;
	
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Activation|Activators", meta = (MustImplement = "/Script/TwistedShadows.TS_Activator"))
	TArray<AActor*> ActorActivators;
	
	virtual void BeginPlay() override;
	

};
