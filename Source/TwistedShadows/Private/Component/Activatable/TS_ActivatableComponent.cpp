// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Activatable/TS_ActivatableComponent.h"
#include "Interfaces/TS_Activatable.h"
#include "Definitions/LogDefinitions.h"
#include "Interfaces/TS_Activator.h"

UTS_ActivatableComponent::UTS_ActivatableComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bCanBeActivate = true;
}

void UTS_ActivatableComponent::BeginPlay()
{
	Super::BeginPlay();

	for (const AActor* Activator : ActorActivators)
	{
		if (UTS_ActivatorComponent* ActivatorComponent = ITS_Activator::Execute_GetActivatorComponent(Activator))
		{
			ActivatorComponent->OnActivationDelegate.AddUniqueDynamic(this, &UTS_ActivatableComponent::ActivateActor);
			ActivatorComponent->OnDeactivationDelegate.AddUniqueDynamic(this, &UTS_ActivatableComponent::DeactivateActor);
		}
	}
}

void UTS_ActivatableComponent::ActivateActor(FActivationPayload Payload)
{
	if (!bCanBeActivate)
	{
		return;
	}

	for (const FGameplayTag& RequiredTag : RequiredTags)
	{
		if (!Payload.ActivationTags.HasTagExact(RequiredTag))
		{
			return;
		}
	}

	if (!GetOwner() || !GetOwner()->IsA<UTS_Activatable>())
	{
		//UE_LOG(LogTwistedShadows, Error, TEXT("Owner of %s is not an activatable"), *GetName());
		return;
	}

	ITS_Activatable::Execute_ActivateActor(GetOwner(), Payload);
}

void UTS_ActivatableComponent::DeactivateActor(FActivationPayload Payload)
{
}




