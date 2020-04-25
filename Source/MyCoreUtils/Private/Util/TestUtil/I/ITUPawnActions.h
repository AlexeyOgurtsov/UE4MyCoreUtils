#pragma once

/**
* Interface that represents actions that the TU Controller knows about.
* We need an interface because not only ATUPawn, but,
* for example ACharacter derived class may also implement the actions.
*/

#include "UObject/Interface.h"
#include "ITUPawnActions.generated.h"

UINTERFACE(BlueprintType)
class UTUPawnActions : public UInterface
{
	GENERATED_BODY()

public:
};

class ITUPawnActions
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Axis_LookPitch(float InAmount);
	virtual void OnController_Axis_LookPitch_Implementation(float InAmount) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Axis_LookYaw(float InAmount);
	virtual void OnController_Axis_LookYaw_Implementation(float InAmount) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Axis_Forward(float InAmount);
	virtual void OnController_Axis_Forward_Implementation(float InAmount) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Axis_Right(float InAmount);
	virtual void OnController_Axis_Right_Implementation(float InAmount) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Axis_Up(float InAmount);
	virtual void OnController_Axis_Up_Implementation(float InAmount) {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_Use();
	virtual void OnController_Action_Use_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_UseTwo();
	virtual void OnController_Action_UseTwo_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_UseThree();
	virtual void OnController_Action_UseThree_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_Fire();
	virtual void OnController_Action_Fire_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_FireTwo();
	virtual void OnController_Action_FireTwo_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_FireThree();
	virtual void OnController_Action_FireThree_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectZero();
	virtual void OnController_Action_SelectZero_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectOne();
	virtual void OnController_Action_SelectOne_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectTwo();
	virtual void OnController_Action_SelectTwo_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectThree();
	virtual void OnController_Action_SelectThree_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectFour();
	virtual void OnController_Action_SelectFour_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectFive();
	virtual void OnController_Action_SelectFive_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectSix();
	virtual void OnController_Action_SelectSix_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectSeven();
	virtual void OnController_Action_SelectSeven_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectEight();
	virtual void OnController_Action_SelectEight_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectNine();
	virtual void OnController_Action_SelectNine_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_OpenGameMenu();
	virtual void OnController_Action_OpenGameMenu_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_CloseGameMenu();
	virtual void OnController_Action_CloseGameMenu_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_DebugOne();
	virtual void OnController_Action_DebugOne_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_DebugTwo();
	virtual void OnController_Action_DebugTwo_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_DebugThree();
	virtual void OnController_Action_DebugThree_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_ActorSelectNext();
	virtual void OnController_Action_ActorSelectNext_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_ActorSelectPrevious();
	virtual void OnController_Action_ActorSelectPrevious_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectNextInventory();
	virtual void OnController_Action_SelectNextInventory_Implementation() {}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Actions)
	void OnController_Action_SelectPreviousInventory();
	virtual void OnController_Action_SelectPreviousInventory_Implementation() {}
};
