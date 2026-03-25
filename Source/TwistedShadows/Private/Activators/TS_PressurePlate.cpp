// Fill out your copyright notice in the Description page of Project Settings.


#include "Activators/TS_PressurePlate.h"

#include "Components/BoxComponent.h"

// Sets default values
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
}


// Called when the game starts or when spawned
void ATS_PressurePlate::BeginPlay()
{
	Super::BeginPlay();

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &ATS_PressurePlate::OnOverlapBegin);
	OverlapComponent->OnComponentEndOverlap.AddDynamic(this, &ATS_PressurePlate::OnOverlapEnd);
}

// Called every frame
void ATS_PressurePlate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATS_PressurePlate::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Begin Overlap"));	
}

void ATS_PressurePlate::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("End Overlap"));	
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

