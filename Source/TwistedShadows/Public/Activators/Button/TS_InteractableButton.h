// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Actors/Interactable/TS_InteractableObject.h"
#include "Interfaces/TS_Activator.h"
#include "TS_InteractableButton.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_InteractableButton : public ATS_InteractableObject, public ITS_Activator
{
	GENERATED_BODY()

public:
	
	ATS_InteractableButton();
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTS_ActivatorComponent> ActivatorComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation | Tags")
	FGameplayTagContainer OverlapTags;
	
	
	
#pragma region ITS_Activatable

public:
	
	virtual bool IsActivatableActorEnabled_Implementation() const override;
	
	virtual UTS_ActivatorComponent* GetActivatorComponent_Implementation() const override;
	
	virtual void ActivateInteractable_Implementation() override;
	
#pragma endregion ITS_Activatable
};
