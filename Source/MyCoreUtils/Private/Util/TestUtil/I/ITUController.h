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

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void Default_Axis_LookPitch(APawn* P, float InAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void Default_Axis_LookYaw(APawn* P, float InAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void Default_Axis_Forward(APawn* P, float InAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void Default_Axis_Right(APawn* P, float InAmount);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Framework)
	void Default_Axis_Up(APawn* P, float InAmount);
};
