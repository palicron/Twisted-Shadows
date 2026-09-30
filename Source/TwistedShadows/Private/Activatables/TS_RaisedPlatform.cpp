// Twisted Shadow make by JSP


#include "Activatables/TS_RaisedPlatform.h"

#include "Components/SplineComponent.h"

// Sets default values
ATS_RaisedPlatform::ATS_RaisedPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	
	RaisedPlatformRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Door Root"));
	SetRootComponent(RaisedPlatformRoot);
	
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SplineComponent->SetupAttachment(RaisedPlatformRoot);
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RaisedPlatformRoot);
	
	StartSplineIndex = 0;
	CurrentSplineIndex = 0;
	LastSplineIndex = 0;
}

void ATS_RaisedPlatform::BeginPlay()
{
	Super::BeginPlay();

	SplinePointsCount = SplineComponent->GetNumberOfSplinePoints();

	if (StartSplineIndex - 1 >= SplinePointsCount)
	{
		StartSplineIndex = SplinePointsCount - 1;
	}
	else if (StartSplineIndex < 0)
	{
		StartSplineIndex = 0;
	}
	else
	{
		CurrentSplineIndex = LastSplineIndex = StartSplineIndex;
	}
	
	MoveToSplinePoint(CurrentSplineIndex);
}


void ATS_RaisedPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATS_RaisedPlatform::MoveToNextSplinePoint()
{
	if (CurrentSplineIndex + 1 > SplinePointsCount - 1)
	{
		//TODO mange return case
		return;
	}
	
	
}

void ATS_RaisedPlatform::MoveToPreviousSplinePoint()
{
}

void ATS_RaisedPlatform::MoveToSplinePoint(int32 SplineIndex)
{
	if (SplineIndex < 0 || SplineIndex >= SplinePointsCount )
	{
		return;
	}
	
	FVector SplineLocation = SplineComponent->GetLocationAtSplinePoint(SplineIndex, ESplineCoordinateSpace::World);
	MeshComponent->SetWorldLocation(SplineComponent->GetLocationAtSplinePoint(SplineIndex, ESplineCoordinateSpace::World));
	
	DrawDebugSphere(GetWorld(), SplineLocation, 10.f, 16, FColor::Red, true, 0.f);
}

void ATS_RaisedPlatform::MoveToLastSplinePoint()
{
}

void ATS_RaisedPlatform::ActivateActor_Implementation(FActivationPayload Payload)
{
	ITS_Activatable::ActivateActor_Implementation(Payload);
}

ETS_ActivationState ATS_RaisedPlatform::GetActivationState_Implementation() const
{
	return ITS_Activatable::GetActivationState_Implementation();
}

int32 ATS_RaisedPlatform::GetActivationPhase_Implementation() const
{
	return ITS_Activatable::GetActivationPhase_Implementation();
}

UTS_ActivatableComponent* ATS_RaisedPlatform::GetActivatableComponent_Implementation() const
{
	return ITS_Activatable::GetActivatableComponent_Implementation();
}


