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
}

void UTS_InteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTS_InteractComponent::ActivateInteraction()
{
	bIsActivate = true;
	LastActivationTime = 0.f;
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


