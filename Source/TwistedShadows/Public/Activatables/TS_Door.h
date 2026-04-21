// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Activatable.h"
#include "Public/Component/Activatable/TS_ActivatableComponent.h"
#include "TS_Door.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDoorStateChangedSignature, ETS_ActivationState, NewSate);
UCLASS()
class TWISTEDSHADOWS_API ATS_Door : public AActor, public ITS_Activatable
{
	GENERATED_BODY()

public:
	ATS_Door();
	
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	ETS_ActivationState GetDoorState() const { return DoorState; }
	
	UPROPERTY(BlueprintAssignable)
	FOnDoorStateChangedSignature OnDoorStateChangedDelegate;
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	uint8 bCanBeActiveOnce : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTS_ActivatableComponent> ActivatableComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* OpenPositionTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USceneComponent* ClosePositionTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	uint8 bStartOpen : 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USceneComponent* DoorRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	virtual void BeginPlay() override;

	ETS_ActivationState DoorState;

#pragma region ITS_Activatable
	
	virtual void ActivateActor_Implementation(FActivationPayload Payload) override;
	virtual void DeactivateActor_Implementation(FActivationPayload Payload) override;
	virtual ETS_ActivationState GetActivationState_Implementation() const override;
	virtual int32 GetActivationPhase_Implementation() const override;
	virtual UTS_ActivatableComponent* GetActivatableComponent_Implementation() const override;
#pragma endregion ITS_Activatable
};
