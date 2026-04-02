// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Activator/TS_ActivatorComponent.h"


UTS_ActivatorComponent::UTS_ActivatorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UTS_ActivatorComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTS_ActivatorComponent::ActivateActors()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Activate!"));	
}

void UTS_ActivatorComponent::DeActivateActors()
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Deactivate!"));	
}

