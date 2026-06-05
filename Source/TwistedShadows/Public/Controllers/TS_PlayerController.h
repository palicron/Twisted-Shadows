// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "Definitions/GeneralDefinitions.h"
#include "TS_PlayerController.generated.h"

class ATS_PlayerCharacter;
class ATS_ShadowCharacter;
class ADecalActor;
class UInputAction;
class ATS_CameraActor;
class UInputMappingContext;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCameraChangedSignature, ATS_CameraActor*, CameraActor);
/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
	
public:
	ATS_PlayerController();
	
	UPROPERTY(BlueprintAssignable)
	FOnCameraChangedSignature OnCameraChangedDelegate;
	
	UFUNCTION(BlueprintCallable)
	ATS_CameraActor* GetCurrentCamera() const { return CurrentCameraActor.Get();}
	
	UFUNCTION(blueprintcallable)
	void SetNewCamera(ATS_CameraActor* NewCamera);
	
	UFUNCTION(BlueprintCallable)
	bool GetIsInShadowCasting() const { return bIsInShadowCasting; }
protected:
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ATS_ShadowCharacter> ShadowCharacterClass;
	
	TWeakObjectPtr<ATS_PlayerCharacter> LastCaster;
	
	TWeakObjectPtr<ATS_ShadowCharacter> ShadowCharacter;
	
	ETS_ShadowCastingState CurrentShadowCastingState;
	
	UPROPERTY(EditAnywhere, Category = "Decal")
	TSubclassOf<ADecalActor>  DecalActorClass;
	
	UPROPERTY(EditAnywhere, Category = "Decal")
	TObjectPtr<ADecalActor> DecalActor;
	
	TWeakObjectPtr<ATS_CameraActor> CurrentCameraActor;
	
	FTimerHandle ShadowCastMouseTrackHandle;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* DefaultMappingContexts;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
    UInputMappingContext* ShadowCastMappingContexts;
    
    UPROPERTY(EditAnywhere, Category="Input")
    UInputAction* ShadowCastInput;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* ShadowClickInput;
	
	UPROPERTY(EditAnywhere, Category = "Selection")
	TEnumAsByte<ETraceTypeQuery> SelectionTraceChannel;
	
	UPROPERTY(EditDefaultsOnly)
	float ShadowMaxCastingDistance;
	
	UPROPERTY(EditDefaultsOnly)
	float ShadowMinCastingDistance;
	
	uint8 bIsInShadowCasting : 1;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	
	void ToggleShadowCasting();

	UFUNCTION()
	virtual void OnShadowCastInput(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OnShadowClickInput(const FInputActionValue& Value);
	
	UFUNCTION()
	void MouseTrackShadowCast();
	
	bool GetLocationUnderCursor(FVector& Location);
	
	UFUNCTION()
	void SpawnAndPossesShadow();
	
	UFUNCTION()
	void PossessLastCaster();
	
	UFUNCTION(blueprintcallable)
	void DestroyShadow();
};
