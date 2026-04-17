// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TS_Savable.h"
#include "TS_GoalActor.generated.h"

class UTS_SaveSubsystem;
class ATS_GameMode_Base;
class UTS_LevelFlowSubsystem;
class USphereComponent;

UCLASS()
class TWISTEDSHADOWS_API ATS_GoalActor : public AActor, public ITS_Savable
{
	GENERATED_BODY()
	
public:	

	ATS_GoalActor();

protected:
	
	TWeakObjectPtr<ATS_GameMode_Base> GameModePtr;

	TWeakObjectPtr<UTS_LevelFlowSubsystem> FlowSubsystem;
	
	TWeakObjectPtr<UTS_SaveSubsystem> SaveSubsystemPtr;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Components")
	uint8 bCanBeActivate : 1;
	
	UPROPERTY(EditDefaultsOnly,blueprintReadOnly,Category = "Components")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly,blueprintReadOnly,Category = "Components")
	TObjectPtr<USphereComponent> PlayerDetectionSphere;
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDetectorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void OnSlotSave_Implementation(UTS_SlotSaveGame* SaveGame) override;
	
	virtual void OnLoadSave_Implementation(const UTS_SlotSaveGame* SaveGame) override;
	
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
