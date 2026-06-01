// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TS_InteractComponent.generated.h"


class ITS_Interactable;

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
	
	UFUNCTION(BlueprintCallable)
	void ActivateInteract() const;
protected:
	
	TWeakObjectPtr<AActor> Owner;
	
	FCollisionQueryParams TraceParams;
	
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
	TEnumAsByte<ECollisionChannel> InteractTraceChanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Interact")
	uint8 bIsActivate : 1;
	
	TWeakObjectPtr<AActor> InteractableActorPtr;
	
	virtual void BeginPlay() override;
	
	void ActivateInteraction();
	
	void DeactivateInteraction();
	

	
	void OnInteractableOverlap();
	
	void OnInteractableEndOverlap();
	
	void StarInteractableTrace();
	
	void StopInteractableTrace();
	
	UFUNCTION()
	void TickTrace();
	
	void TryToSetInteractable(const TArray<FHitResult> DetectActors);
	
	FTimerHandle InteractCheckTimerHandle;
	
	
	
};
