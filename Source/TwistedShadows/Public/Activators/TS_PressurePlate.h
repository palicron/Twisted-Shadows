// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Activator.h"
#include "TS_PressurePlate.generated.h"

UCLASS()
class TWISTEDSHADOWS_API ATS_PressurePlate : public AActor, public ITS_Activator
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATS_PressurePlate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
#pragma region ITS_Activatable

	virtual void ActivateActivatableActors_Implementation() override;
	
	virtual void DeactivateActivatableActors_Implementation() override;
	
	virtual bool IsActivatableActorEnabled_Implementation() const override;
	
	virtual TArray<TScriptInterface<ITS_Activatable>> GetActivatableActors_Implementation() const override;
#pragma endregion ITS_Activatable
	
};
