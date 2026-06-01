// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TS_Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTS_Interactable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TWISTEDSHADOWS_API ITS_Interactable
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteractSelect();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnInteractDeselect();
	
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ActivateInteractable();
};
