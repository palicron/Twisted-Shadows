// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Activator/TS_ActivatorComponent.h"

#include "Definitions/GeneralDefinitions.h"


UTS_ActivatorComponent::UTS_ActivatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTS_ActivatorComponent::ActivateActors(AActor* Instigator)
{
	FActivationPayload Payload;

	Payload.Instigator = Instigator;
	Payload.InstigatorActivator = GetOwner();
	Payload.ActivationTime = GetWorld()->GetTimeSeconds();

	for (FGameplayTag ActivationTag : ActivationTags)
	{
		Payload.ActivationTags.AddTag(ActivationTag);
	}

	OnActivationDelegate.Broadcast(Payload);
}

void UTS_ActivatorComponent::DeActivateActors(AActor* Instigator)
{
	FActivationPayload Payload;

	Payload.Instigator = Instigator;
	Payload.InstigatorActivator = GetOwner();
	Payload.ActivationTime = GetWorld()->GetTimeSeconds();

	for (FGameplayTag ActivationTag : DeactivationTags)
	{
		Payload.ActivationTags.AddTag(ActivationTag);
	}

	OnDeactivationDelegate.Broadcast(Payload);
}

