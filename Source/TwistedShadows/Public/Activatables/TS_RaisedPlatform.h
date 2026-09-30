// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Activatable.h"
#include "TS_RaisedPlatform.generated.h"

class USplineComponent;

UCLASS()
class TWISTEDSHADOWS_API ATS_RaisedPlatform : public AActor, public ITS_Activatable
{
	GENERATED_BODY()
	
public:	
	
	ATS_RaisedPlatform();
	virtual void Tick(float DeltaTime) override;
	
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USplineComponent> SplineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* RaisedPlatformRoot;
	
	ETS_ActivationState RaisedPlatformState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Spline")
	int32 StartSplineIndex;
	
	int32 CurrentSplineIndex;
	
	int32 LastSplineIndex;
	
	int32 SplinePointsCount;
	
	virtual void BeginPlay() override;
	
	virtual void MoveToNextSplinePoint();
	
	virtual void MoveToPreviousSplinePoint();
	
	virtual void MoveToSplinePoint(int32 SplineIndex);
	
	virtual void MoveToLastSplinePoint();

public:
#pragma region ITS_Activatable
	
	virtual void ActivateActor_Implementation(FActivationPayload Payload) override;

	virtual ETS_ActivationState GetActivationState_Implementation() const override;
	virtual int32 GetActivationPhase_Implementation() const override;
	virtual UTS_ActivatableComponent* GetActivatableComponent_Implementation() const override;
#pragma endregion ITS_Activatable
	
	
	
};
