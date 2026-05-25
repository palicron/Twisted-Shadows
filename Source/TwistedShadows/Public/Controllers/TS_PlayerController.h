// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TS_PlayerController.generated.h"

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
protected:
	
	TWeakObjectPtr<ATS_CameraActor> CurrentCameraActor;
	
	UPROPERTY(EditAnywhere, Category ="Input|Input Mappings")
	UInputMappingContext* DefaultMappingContexts;
	
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;
	


	
};
