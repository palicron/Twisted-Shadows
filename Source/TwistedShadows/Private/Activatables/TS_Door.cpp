// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Activatables/TS_Door.h"


// Sets default values
ATS_Door::ATS_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATS_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATS_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATS_Door::ActivateActor_Implementation()
{
	ITS_Activatable::ActivateActor_Implementation();
}

void ATS_Door::DeactivateActor_Implementation()
{
	ITS_Activatable::DeactivateActor_Implementation();
}

ETS_ActivationState ATS_Door::GetActivationState_Implementation() const
{
	return ITS_Activatable::GetActivationState_Implementation();
}

int32 ATS_Door::GetActivationPhase_Implementation() const
{
	return ITS_Activatable::GetActivationPhase_Implementation();
}

