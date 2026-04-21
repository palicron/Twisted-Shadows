// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Activatables/TS_Door.h"


ATS_Door::ATS_Door()
{
	PrimaryActorTick.bCanEverTick = true;
	
	DoorRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Door Root"));
	SetRootComponent(DoorRoot);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(DoorRoot);
	
	OpenPositionTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Open Position Target"));
	ClosePositionTarget = CreateDefaultSubobject<USceneComponent>(TEXT("Close Position Target"));
	
	DoorState = ETS_ActivationState::Deactivated;
	
	bCanBeActiveOnce = false;
	ActivatableComponent = CreateDefaultSubobject<UTS_ActivatableComponent>(TEXT("Activatable Component"));
}

void ATS_Door::BeginPlay()
{
	Super::BeginPlay();
	
	if (bStartOpen)
	{
		DoorState = ETS_ActivationState::Activated;
		MeshComponent->SetRelativeLocation(OpenPositionTarget->GetRelativeLocation());
	}
}

void ATS_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATS_Door::ActivateActor_Implementation(FActivationPayload Payload)
{
	//TODO this shoudl be a timelein fo rtth emomento is just set 
	
	if (bCanBeActiveOnce && DoorState == ETS_ActivationState::Activated)
	{
		return;
	}
	
	if (DoorState == ETS_ActivationState::Deactivated)
	{
		DoorState = ETS_ActivationState::Activated;
		MeshComponent->SetRelativeLocation(OpenPositionTarget->GetRelativeLocation());
	}
	else if (DoorState == ETS_ActivationState::Activated)
	{
		DoorState = ETS_ActivationState::Deactivated;
		MeshComponent->SetRelativeLocation(ClosePositionTarget->GetRelativeLocation());
	}

	OnDoorStateChangedDelegate.Broadcast(DoorState);
}

void ATS_Door::DeactivateActor_Implementation(FActivationPayload Payload)
{
	if (DoorState == ETS_ActivationState::Deactivated || bCanBeActiveOnce)
	{
		return;
	}
	
	DoorState = ETS_ActivationState::Deactivated;
	MeshComponent->SetRelativeLocation(ClosePositionTarget->GetRelativeLocation());
}

ETS_ActivationState ATS_Door::GetActivationState_Implementation() const
{
	return DoorState;
}

int32 ATS_Door::GetActivationPhase_Implementation() const
{
	return ITS_Activatable::GetActivationPhase_Implementation();
}

UTS_ActivatableComponent* ATS_Door::GetActivatableComponent_Implementation() const
{
	return ActivatableComponent;
}

