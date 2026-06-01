// Twisted Shadow make by JSP


#include "Actors/Interactable/TS_InteractableObject.h"

// Sets default values
ATS_InteractableObject::ATS_InteractableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void ATS_InteractableObject::BeginPlay()
{
	Super::BeginPlay();
	
}


void ATS_InteractableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATS_InteractableObject::OnInteractSelect_Implementation()
{
	ITS_Interactable::OnInteractSelect_Implementation();
}

void ATS_InteractableObject::OnInteractDeselect_Implementation()
{
	ITS_Interactable::OnInteractDeselect_Implementation();
}

void ATS_InteractableObject::ActivateInteractable_Implementation()
{
	ITS_Interactable::ActivateInteractable_Implementation();
}
