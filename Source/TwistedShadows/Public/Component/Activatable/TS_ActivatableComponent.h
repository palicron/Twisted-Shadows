// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Definitions/GeneralDefinitions.h"
#include "Interfaces/TS_Activatable.h"
#include "TS_ActivatableComponent.generated.h"

USTRUCT(BlueprintType)
struct FBindingStruct
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , meta = (GetOptions = "GetBindableFunctionNames"))
	TMap<FGameplayTag, FName> FunctionBinding;
};

class ITS_Activator;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TWISTEDSHADOWS_API UTS_ActivatableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UTS_ActivatableComponent();

	UFUNCTION(BlueprintCallable, meta = (BindableActivation))
	virtual void ActivateActor(FActivationPayload Payload);


protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	uint8 bCanBeActivate : 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	TArray<FGameplayTag> RequiredTags;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Conditions")
	TArray<FGameplayTag> RequiredDeactivationTags;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Activation|Activators", meta = (MustImplement = "/Script/TwistedShadows.TS_Activator"))
	TArray<AActor*> ActorActivators;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Activation|Activators")
	TMap<AActor*,FBindingStruct> ActivatorMap;
	
	virtual void BeginPlay() override;
	
	UFUNCTION()
	TArray<FString> GetBindableFunctionNames() const;
	

};
