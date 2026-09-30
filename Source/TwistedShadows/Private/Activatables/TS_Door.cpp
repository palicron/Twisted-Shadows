// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Activatables/TS_Door.h"

#include "Algo/ForEach.h"
#include "Functions/TSStatics.h"


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
	
	if (UTSStatics::CanBeActivate(OpenTag,Payload.ActivationTags))
	{
		OpenDoor();
		return;
	}
	
	if (UTSStatics::CanBeActivate(CloseTag, Payload.ActivationTags))
	{
		CloseDoor();
		return;
	}
	
	if (UTSStatics::CanBeActivate(FlipFlopTag, Payload.ActivationTags))
	{
		FlipFLopDoor();
	}
	
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

void ATS_Door::OpenDoor()
{
	if (DoorState == ETS_ActivationState::Activated)
	{
		return;
	}
	
	DoorState = ETS_ActivationState::Activated;
	MeshComponent->SetRelativeLocation(OpenPositionTarget->GetRelativeLocation());
	OnDoorStateChangedDelegate.Broadcast(DoorState);
}

void ATS_Door::CloseDoor()
{
	
	if (DoorState == ETS_ActivationState::Deactivated)
	{
		return;
	}
	
	DoorState = ETS_ActivationState::Deactivated;
	MeshComponent->SetRelativeLocation(ClosePositionTarget->GetRelativeLocation());
	OnDoorStateChangedDelegate.Broadcast(DoorState);
}

void ATS_Door::FlipFLopDoor()
{
	if (DoorState == ETS_ActivationState::Deactivated)
	{
		OpenDoor();
	}
	else if (DoorState == ETS_ActivationState::Activated)
	{
		CloseDoor();
	}
}
