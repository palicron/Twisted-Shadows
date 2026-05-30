// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TS_InteractComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWISTEDSHADOWS_API UTS_InteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTS_InteractComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool IsInteract() const { return bIsActivate; }

	UFUNCTION(BlueprintCallable)
	void SetIsInteract(const bool InbIsActivate) { bIsActivate = InbIsActivate; };
protected:
	
	TWeakObjectPtr<AActor> Owner;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	TEnumAsByte<ECollisionChannel> InteractTraceChanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	float InteractCoolDown;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	float InteractRadius;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	float InteractCheckTick;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	float InteractMinDotAngle;
	
	float LastActivationTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	uint8 bIsActivate : 1;
	
	TWeakObjectPtr<AActor> InteractableActor;
	
	virtual void BeginPlay() override;

	void ActivateInteraction();

	void DeactivateInteraction();
	
	void CheckInteract();
	
	void ActivateInteract();
	
	void OnInteractableOverlap();
	
	void OnInteractableEndOverlap();
	
	void StarInteractableTrace();
	
	UFUNCTION()
	void TickTrace();
	
	
	FTimerHandle InteractCheckTimerHandle;
	
	
	
};
