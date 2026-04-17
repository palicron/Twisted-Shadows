// Twisted Shadow make by JSP

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TS_Savable.generated.h"

class UTS_SlotSaveGame;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTS_Savable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TWISTEDSHADOWS_API ITS_Savable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnSlotSave(UTS_SlotSaveGame* SaveGame);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnLoadSave(const UTS_SlotSaveGame* SaveGame);
};
