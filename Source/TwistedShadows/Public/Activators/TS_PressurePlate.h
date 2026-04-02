// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Activator.h"
#include "TS_PressurePlate.generated.h"

class UBoxComponent;

UCLASS()
class TWISTEDSHADOWS_API ATS_PressurePlate : public AActor, public ITS_Activator
{
	GENERATED_BODY()
	
public:	

	ATS_PressurePlate();
	
	virtual void Tick(float DeltaTime) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* OverlapComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UTS_ActivatorComponent> ActivatorComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	float MinWeightToActivate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	uint8 bIsActivate : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	uint8 bUseWeightToActivate : 1;
	
	TArray<AActor*> OverlappingActors;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_ActivatePlate() const;
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_DeactivatePlate();
	
#pragma region ITS_Activatable

public:
	
	virtual bool IsActivatableActorEnabled_Implementation() const override;
	
	virtual UTS_ActivatorComponent* GetActivatorComponent_Implementation() const override;
	
#pragma endregion ITS_Activatable
	
};
