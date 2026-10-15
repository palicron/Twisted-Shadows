// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Definitions/GeneralDefinitions.h"
#include "Definitions/PlayerDefinitions.h"
#include "GameFramework/Character.h"
#include "TS_PlayerCharacter.generated.h"

class UTS_InteractComponent;
class ATS_CameraActor;
class ATS_PlayerController;
class UInputAction;

UCLASS()
class TWISTEDSHADOWS_API ATS_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	ATS_PlayerCharacter();
	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnGoalTouch();
	
	UFUNCTION(BlueprintCallable)
	ETS_CharacterClass GetCharacterClass() const { return CharacterClass;}
	
	UFUNCTION(BlueprintCallable)
	virtual void StartGrabbingActor(AActor* ActorToGrab, USceneComponent* GrabbingPoint,const ETS_MovementType MovementType);
	
	virtual void MoveToGrabPoint(USceneComponent* GrabbingPoint);
	
	UFUNCTION(BlueprintCallable)
	virtual void EndeGrabbingActor();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<UTS_InteractComponent> PlayerInteractComponent;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
	
	TWeakObjectPtr<ATS_PlayerController> PlayerController;
	
	TWeakObjectPtr<ATS_CameraActor> CurrentCamera;
	
	TWeakObjectPtr<AActor> GrabbedActor;
	FVector StartPosition;
	
	UPROPERTY(BlueprintReadOnly)
	FVector CurrentForwardVector;
	
	UPROPERTY(BlueprintReadOnly)
	FVector CurrentRightVector;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = "Movement")
	ETS_MovementType CurrentMovementType;

	UPROPERTY(EditDefaultsOnly, blueprintReadOnly, Category= "Character | Type")
	ETS_CharacterClass CharacterClass;
	
	FTimerHandle GrabbingTimerHandle;
	
	virtual void BeginPlay() override;
	 
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void StartedInteract(const FInputActionValue& Value);
	
	UFUNCTION()
	virtual void OngoingInteract(const FInputActionInstance& Value);
	
	UFUNCTION()
	virtual void EndInteract(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnCameraChangeCallback(ATS_CameraActor* NewCamera);
	
	
	
};
