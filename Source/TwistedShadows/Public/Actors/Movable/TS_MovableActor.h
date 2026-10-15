// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actors/Interactable/TS_InteractableObject.h"
#include "TS_MovableActor.generated.h"

UCLASS()
class TWISTEDSHADOWS_API ATS_MovableActor : public ATS_InteractableObject
{
	GENERATED_BODY()
	
public:	

	ATS_MovableActor();

	virtual void Tick(float DeltaTime) override;

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Snap")
	TArray<USceneComponent*> SnapComponents;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;
	
	virtual void BeginPlay() override;
	
	virtual void ActivateInteractable_Implementation(const FInteractPayload Payload) override;
	
	USceneComponent* GetNearestSnapComponent(const FVector Location);

};
