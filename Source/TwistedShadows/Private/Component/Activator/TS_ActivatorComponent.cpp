// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Activator/TS_ActivatorComponent.h"

#include "Definitions/GeneralDefinitions.h"


UTS_ActivatorComponent::UTS_ActivatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTS_ActivatorComponent::ActivateActors(const FGameplayTagContainer ActivationTags, AActor* Instigator)
{
	FActivationPayload Payload;

	Payload.Instigator = Instigator;
	Payload.InstigatorActivator = GetOwner();
	Payload.ActivationTime = GetWorld()->GetTimeSeconds();
	Payload.ActivationTags = ActivationTags;
	
	OnActivationDelegate.Broadcast(Payload);
}

