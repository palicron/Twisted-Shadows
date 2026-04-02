// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TS_ActivatorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TWISTEDSHADOWS_API UTS_ActivatorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UTS_ActivatorComponent();

protected:

	virtual void BeginPlay() override;

public:	
	
	UFUNCTION(BlueprintCallable)
	virtual void ActivateActors();

	UFUNCTION(BlueprintCallable)
	virtual void DeActivateActors();
};
