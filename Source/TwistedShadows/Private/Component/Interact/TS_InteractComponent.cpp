// Twisted Shadow make by JSP


#include "Component/Interact/TS_InteractComponent.h"

#include "TwistedShadows.h"
#include "Interfaces/TS_Interactable.h"


UTS_InteractComponent::UTS_InteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsActivate = false;
	InteractCheckTick = 0.15f;
	InteractMinDotAngle = 0.5f;
	InteractCoolDown = 0.3f;
	LastActivationTime = 0.f;
	
	TraceParams.AddIgnoredActor(Owner.Get());
	
}

void UTS_InteractComponent::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
	ActivateInteraction();
}

void UTS_InteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTS_InteractComponent::ActivateInteraction()
{
	if (bIsActivate)
	{
		return;
	}

	bIsActivate = true;
	LastActivationTime = 0.f;

	StarInteractableTrace();
}

void UTS_InteractComponent::DeactivateInteraction()
{
	bIsActivate = false;
	StopInteractableTrace();
}

void UTS_InteractComponent::ActivateInteract() const
{
	if (!bIsActivate || !InteractableActorPtr.IsValid())
	{
		return;
	}
	
	ITS_Interactable::Execute_ActivateInteractable(InteractableActorPtr.Get());
	
}

void UTS_InteractComponent::OnInteractableOverlap()
{
}

void UTS_InteractComponent::OnInteractableEndOverlap()
{
}

void UTS_InteractComponent::StarInteractableTrace()
{
	if (!bIsActivate || GetWorld()->GetTimerManager().IsTimerActive(InteractCheckTimerHandle))
	{
		return;
	}
	
	if (!Owner.IsValid())
	{
		Owner = GetOwner();
		if (!Owner.IsValid())
		{
			return;
		}
	}
	
	GetWorld()->GetTimerManager().SetTimer(InteractCheckTimerHandle,this,&UTS_InteractComponent::TickTrace,InteractCheckTick,{.bLoop = true,.bMaxOncePerFrame = true});
}

void UTS_InteractComponent::StopInteractableTrace()
{
	GetWorld()->GetTimerManager().ClearTimer(InteractCheckTimerHandle);
}

void UTS_InteractComponent::TickTrace()
{
	if (!Owner.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(InteractCheckTimerHandle);
		return;
	}
	
	
	TArray<FHitResult> InteractableHits;
	FVector CenterTrace = Owner->GetActorLocation();
	FCollisionShape Sphere = FCollisionShape::MakeSphere(InteractRadius);

	if (GetWorld()->SweepMultiByChannel(
		InteractableHits,
		CenterTrace,
		CenterTrace,
		FQuat::Identity,
		INTERACTABLE_TRACE_CHANNEL,
		Sphere,
		TraceParams
	))
	{
		TryToSetInteractable(InteractableHits);
	}
	else if (InteractableActorPtr.IsValid())
	{
		ITS_Interactable::Execute_OnInteractDeselect(InteractableActorPtr.Get());
		OnInteractableEndOverlap();
		InteractableActorPtr = nullptr;
	}

	//@TODO: in later proposition check if ther wall
}

void UTS_InteractComponent::TryToSetInteractable(const TArray<FHitResult> DetectActors)
{
	float MinDistance = 9999999.f;
	float MinDotAngle = 0.f;
	AActor* TempInteractableActorPtr = nullptr;
	
	for (const FHitResult& HitResult : DetectActors)
	{
		if (!HitResult.GetActor() || !HitResult.GetActor()->Implements<UTS_Interactable>())
		{
			continue;
		}
		AActor* Actor = HitResult.GetActor();
		FVector InteractableActorVector = Actor->GetActorLocation() - Owner->GetActorLocation();
		float DotProduct = FVector::DotProduct(Owner->GetActorForwardVector(), InteractableActorVector);
		if (DotProduct < InteractMinDotAngle || DotProduct < MinDotAngle)
		{
			continue;
		}

		if (InteractableActorVector.Size() >= MinDistance)
		{
			continue;
		}

		MinDistance = InteractableActorVector.Size();
		MinDotAngle = DotProduct;
		TempInteractableActorPtr = Actor;
	}

	if (!TempInteractableActorPtr)
	{
		if (InteractableActorPtr.IsValid())
		{
			ITS_Interactable::Execute_OnInteractDeselect(InteractableActorPtr.Get());
			OnInteractableEndOverlap();
			InteractableActorPtr = nullptr;
			return;
		}
	}
	
	if (InteractableActorPtr == TempInteractableActorPtr)
	{
		return;
	}
	
	if (InteractableActorPtr.IsValid())
	{
		ITS_Interactable::Execute_OnInteractDeselect(InteractableActorPtr.Get());
	}
	
	InteractableActorPtr = TempInteractableActorPtr;
	ITS_Interactable::Execute_OnInteractSelect(InteractableActorPtr.Get());
	
	OnInteractableOverlap();
}


