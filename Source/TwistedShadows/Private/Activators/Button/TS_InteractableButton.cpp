// Twisted Shadow make by JSP


#include "Activators/Button/TS_InteractableButton.h"

ATS_InteractableButton::ATS_InteractableButton()
{
	ActivatorComponent = CreateDefaultSubobject<UTS_ActivatorComponent>(TEXT("ActivatorComponent"));
}

bool ATS_InteractableButton::IsActivatableActorEnabled_Implementation() const
{

	return true;
}

UTS_ActivatorComponent* ATS_InteractableButton::GetActivatorComponent_Implementation() const
{
	return ActivatorComponent;
}

void ATS_InteractableButton::ActivateInteractable_Implementation()
{
	ActivatorComponent->ActivateActors(OverlapTags);
	///TODO: Player send constan check shoudl limt this here
}
