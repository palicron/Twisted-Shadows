// Fill out your copyright notice in the Description page of Project Settings.


#include "Activators/TS_PressurePlate.h"

// Sets default values
ATS_PressurePlate::ATS_PressurePlate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATS_PressurePlate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATS_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATS_PressurePlate::ActivateActivatableActors_Implementation()
{
	ITS_Activator::ActivateActivatableActors_Implementation();
}

void ATS_PressurePlate::DeactivateActivatableActors_Implementation()
{
	ITS_Activator::DeactivateActivatableActors_Implementation();
}

bool ATS_PressurePlate::IsActivatableActorEnabled_Implementation() const
{
	return ITS_Activator::IsActivatableActorEnabled_Implementation();
}

TArray<TScriptInterface<ITS_Activatable>> ATS_PressurePlate::GetActivatableActors_Implementation() const
{
	return ITS_Activator::GetActivatableActors_Implementation();
}

