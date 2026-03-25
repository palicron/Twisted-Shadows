// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Activatable.h"
#include "TS_Door.generated.h"

UCLASS()
class TWISTEDSHADOWS_API ATS_Door : public AActor, public ITS_Activatable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATS_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
#pragma region ITS_Activatable
	
	virtual void ActivateActor_Implementation() override;
	virtual void DeactivateActor_Implementation() override;
	virtual ETS_ActivationState GetActivationState_Implementation() const override;
	virtual int32 GetActivationPhase_Implementation() const override;
#pragma endregion ITS_Activatable
};
