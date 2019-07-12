#pragma once

#include "UObject/Interface.h"
#include "ITUController.generated.h"

UINTERFACE()
class UTUController: public UInterface
{
	GENERATED_BODY()
};

class ITUController
{
	GENERATED_BODY()

public:
	/**
	* Called when controlled pawn's BeginPlay is called fully.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void PawnBeginPlayEnded();
};
