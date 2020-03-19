#pragma once

#include "GameFramework/Character.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "I/ITUPawnActions.h"
#include "TUCharacter.generated.h"

class ITUController;

UCLASS()
class ATUCharacter 
: public ACharacter
, public ITUPawnActions
{
	GENERATED_BODY()

public:
	ATUCharacter();

	// ~ITUPawnActions Begin
	// This section contains notifying functions about the controller's actions
	virtual void OnController_Axis_LookPitch_Implementation(float InAmount) override;
	virtual void OnController_Axis_LookYaw_Implementation(float InAmount) override;
	virtual void OnController_Axis_Forward_Implementation(float InAmount) override;
	virtual void OnController_Axis_Right_Implementation(float InAmount) override;
	virtual void OnController_Axis_Up_Implementation(float InAmount) override;
	virtual void OnController_Action_Use_Implementation() override;
	virtual void OnController_Action_UseTwo_Implementation() override;
	virtual void OnController_Action_UseThree_Implementation() override;
	virtual void OnController_Action_Fire_Implementation() override;
	virtual void OnController_Action_FireTwo_Implementation() override;
	virtual void OnController_Action_FireThree_Implementation() override;
	virtual void OnController_Action_SelectZero_Implementation() override;
	virtual void OnController_Action_SelectOne_Implementation() override;
	virtual void OnController_Action_SelectTwo_Implementation() override;
	virtual void OnController_Action_SelectThree_Implementation() override;
	virtual void OnController_Action_SelectFour_Implementation() override;
	virtual void OnController_Action_SelectFive_Implementation() override;
	virtual void OnController_Action_SelectSix_Implementation() override;
	virtual void OnController_Action_SelectSeven_Implementation() override;
	virtual void OnController_Action_SelectEight_Implementation() override;
	virtual void OnController_Action_SelectNine_Implementation() override;
	virtual void OnController_Action_OpenGameMenu_Implementation() override;
	virtual void OnController_Action_CloseGameMenu_Implementation() override;
	virtual void OnController_Action_DebugOne_Implementation() override;
	virtual void OnController_Action_DebugTwo_Implementation() override;
	virtual void OnController_Action_DebugThree_Implementation() override;
	// ~ITUPawnActions End
	
	// ~Controller Begin
	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUController"))
	TScriptInterface<ITUController> K2GetTUController() const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerLogged"))
	TScriptInterface<ITUController> K2GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller, Meta=(DisplayName="GetTUControllerChecked"))
	TScriptInterface<ITUController> K2GetTUControllerChecked() const;

	ITUController* GetTUController() const;
	ITUController* GetTUControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;
	ITUController* GetTUControllerChecked() const ;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	AController* GetControllerChecked() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	UFUNCTION(BlueprintPure, Category = Controller)
	APlayerController* GetPCChecked() const;
	// ~Controller End

	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	/**
	* If true, we log non-periodic big events, like BeginPlay, Possess etc.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Test", Meta=(AllowPrivateAccess = true))
	bool bLogBigEvents = true;
	// ~Logging End
};
