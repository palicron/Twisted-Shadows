// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "TS_PlayerCharacter.generated.h"

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
	
protected:
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* InteractAction;
	
	TWeakObjectPtr<ATS_PlayerController> PlayerController;
	
	TWeakObjectPtr<ATS_CameraActor> CurrentCamera;
	
	UPROPERTY(BlueprintReadOnly)
	FVector CurrentForwardVector;
	
	UPROPERTY(BlueprintReadOnly)
	FVector CurrentRightVector;
	
	virtual void BeginPlay() override;
	 
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	
	UFUNCTION()
	void OnCameraChangeCallback(ATS_CameraActor* NewCamera);
	
	
	
};
