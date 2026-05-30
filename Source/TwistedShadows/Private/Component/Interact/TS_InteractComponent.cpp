// Twisted Shadow make by JSP


#include "Component/Interact/TS_InteractComponent.h"


UTS_InteractComponent::UTS_InteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	bIsActivate = true;
	InteractCheckTick = 0.15f;
	InteractMinDotAngle = 0.5f;
	InteractCoolDown = 0.3f;
	LastActivationTime = 0.f;
}


void UTS_InteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Owner = GetOwner();
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
}

void UTS_InteractComponent::CheckInteract()
{
}

void UTS_InteractComponent::ActivateInteract()
{
	if (!bIsActivate || !InteractableActor.IsValid())
	{
		return;
	}
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

void UTS_InteractComponent::TickTrace()
{
	//Trace a spehre
	//If more tha one check fir distance and then angel, pick the lowes
	// check if the same we ahve alraedy,
	//is diferen set it and call end ovelpay in the old one
	//is there no colliition call overlap end
	//@TODO: in later proposition check if ther wall
	
}


