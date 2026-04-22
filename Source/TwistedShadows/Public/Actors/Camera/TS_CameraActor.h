// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "TS_CameraActor.generated.h"

/**
 * 
 */
UCLASS()
class TWISTEDSHADOWS_API ATS_CameraActor : public ACameraActor
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	FVector GetCameraRightVector() const { return GetActorRightVector(); }
	
	UFUNCTION(BlueprintCallable)
	FVector GetCameraForwardVector() const;
protected:
	

	
	virtual void BeginPlay() override;
	
};
