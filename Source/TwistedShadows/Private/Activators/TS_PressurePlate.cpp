// Fill out your copyright notice in the Description page of Project Settings.


#include "Activators/TS_PressurePlate.h"

#include "Components/BoxComponent.h"
#include "Interfaces/TS_Activatable.h"

//-------------------------------------------------------------------------------------------------------------------------------------------
ATS_PressurePlate::ATS_PressurePlate()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap Component"));
	OverlapComponent->SetupAttachment(MeshComponent);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

	bIsActivate = false;
	bUseWeightToActivate = true;
	MinWeightToActivate = 1.f;
	
	ActivatorComponent = CreateDefaultSubobject<UTS_ActivatorComponent>(TEXT("Activator Component"));
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void ATS_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ATS_PressurePlate::OnOverlapBegin);
	OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &ATS_PressurePlate::OnOverlapEnd);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void ATS_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void ATS_PressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                       const FHitResult& SweepResult)
{
	if (bIsActivate)
	{
		return;
	}
	
	bIsActivate = true;
	
	OverlappingActors.AddUnique(OtherActor);
	ActivatorComponent->ActivateActors();
	
	BP_ActivatePlate();
}

//-------------------------------------------------------------------------------------------------------------------------------------------
void ATS_PressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OverlappingActors.Contains(OtherActor))
	{
		OverlappingActors.Remove(OtherActor);
	}

	if (OverlappingActors.Num() == 0)
	{
		bIsActivate = false;
		ActivatorComponent->DeActivateActors();
		BP_DeactivatePlate();
	}
}

//-------------------------------------------------------------------------------------------------------------------------------------------
bool ATS_PressurePlate::IsActivatableActorEnabled_Implementation() const
{
	return bIsActivate;
}

//---------------------------------------------------------------------------------------------------------------------------------------------
UTS_ActivatorComponent* ATS_PressurePlate::GetActivatorComponent_Implementation() const
{
	return ActivatorComponent;
}

