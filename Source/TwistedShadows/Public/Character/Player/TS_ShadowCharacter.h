// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Character/Player/TS_PlayerCharacter.h"
#include "TS_ShadowCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShadowDestroySignature);
class ATS_CasterCharacter;
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_ShadowCharacter : public ATS_PlayerCharacter
{
	GENERATED_BODY()

public:
	
	ATS_ShadowCharacter();
	
	UFUNCTION()
	void SetUpShadowInfo(ATS_PlayerCharacter* Caster, const FVector& ShadowLocation);
	
	UFUNCTION( BlueprintCallable)
	void DestroyShadow();

	UPROPERTY(BlueprintAssignable)
	FOnShadowDestroySignature OnShadowDestroyDelegate;
protected:
	
	FTimerHandle ShadowLifeTimerHandle;
	
	FVector ShadowStartingLocation;
	
	TWeakObjectPtr<ATS_PlayerCharacter> CasterPtr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shadow")
	float ShadowLifeTime;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shadow")
	float ShadowMaxRange;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shadow")
	float ShadowMinRange;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shadow")
	float CheckTickRate;
	
	float CurrentShadowLifeTime;
	
	UFUNCTION()
	void CheckShadowLife();


};
