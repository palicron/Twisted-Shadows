// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Interactable.h"
#include "TS_InteractableObject.generated.h"

UCLASS()
class TWISTEDSHADOWS_API ATS_InteractableObject : public AActor, public ITS_Interactable
{
	GENERATED_BODY()
	
public:	
	
	ATS_InteractableObject();
	virtual void Tick(float DeltaTime) override;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void OnInteractSelect_Implementation() override;
	
	virtual void OnInteractDeselect_Implementation() override;
	
	virtual void ActivateInteractable_Implementation() override;
	
};
