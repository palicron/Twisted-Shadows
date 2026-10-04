// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Definitions/ActivableSystemDefinitions.h"
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
	TObjectPtr<UTS_ActivatableComponent> ActivatableComponent;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* RaisedPlatformRoot;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Tags")
	FActivationSettings RaisedTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Tags")
	FActivationSettings LowerTag;

	ETS_ActivationState RaisedPlatformState;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Spline")
	int32 StartSplineIndex;
	
	int32 CurrentSplineIndex;
	
	int32 LastSplineIndex;
	
	int32 SplinePointsCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components|Config")
	uint8 bCanBeActiveOnce :1 ;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(blueprintCallable)
	virtual void MoveToNextSplinePoint();
	
	UFUNCTION(blueprintCallable)
	virtual void MoveToPreviousSplinePoint();
	
	UFUNCTION(blueprintCallable)
	virtual void MoveToSplinePoint(int32 SplineIndex);
	
	UFUNCTION(blueprintCallable)
	virtual void MoveToLastSplinePoint();
	
	UFUNCTION(blueprintCallable)
	void FlipFlopPlatform();

public:
#pragma region ITS_Activatable
	
	virtual void ActivateActor_Implementation(FActivationPayload Payload) override;

	virtual ETS_ActivationState GetActivationState_Implementation() const override;
	virtual int32 GetActivationPhase_Implementation() const override;
	virtual UTS_ActivatableComponent* GetActivatableComponent_Implementation() const override;
#pragma endregion ITS_Activatable
	
	
	
};
