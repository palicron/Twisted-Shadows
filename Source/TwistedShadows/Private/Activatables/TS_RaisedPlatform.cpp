// Twisted Shadow make by JSP


#include "Activatables/TS_RaisedPlatform.h"

#include "Component/Activatable/TS_ActivatableComponent.h"
#include "Components/SplineComponent.h"
#include "Functions/TSStatics.h"

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
	
	ActivatableComponent = CreateDefaultSubobject<UTS_ActivatableComponent>(TEXT("Activatable Component"));
	
	StartSplineIndex = 0;
	CurrentSplineIndex = 0;
	LastSplineIndex = 0;
	bCanBeActiveOnce = false;

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
	CurrentSplineIndex++;
	
	MoveToSplinePoint(CurrentSplineIndex);
	
}

void ATS_RaisedPlatform::MoveToPreviousSplinePoint()
{
	if (CurrentSplineIndex - 1 < 0)
	{
		//TODO mange return case
		return;
	}
	CurrentSplineIndex--;

	MoveToSplinePoint(CurrentSplineIndex);
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

void ATS_RaisedPlatform::FlipFlopPlatform()
{
}

void ATS_RaisedPlatform::ActivateActor_Implementation(FActivationPayload Payload)
{
	
	if (bCanBeActiveOnce && RaisedPlatformState == ETS_ActivationState::Activated)
	{
		return;
	}
	
	if (UTSStatics::CanBeActivate(RaisedTag,Payload.ActivationTags))
	{
		MoveToNextSplinePoint();
		return;
	}
	
	if (UTSStatics::CanBeActivate(LowerTag,Payload.ActivationTags))
	{
		MoveToPreviousSplinePoint();
		return;
	}
	
	
}

ETS_ActivationState ATS_RaisedPlatform::GetActivationState_Implementation() const
{
	return RaisedPlatformState;
}

int32 ATS_RaisedPlatform::GetActivationPhase_Implementation() const
{
	return ITS_Activatable::GetActivationPhase_Implementation();
}

UTS_ActivatableComponent* ATS_RaisedPlatform::GetActivatableComponent_Implementation() const
{
	return ActivatableComponent;
}


