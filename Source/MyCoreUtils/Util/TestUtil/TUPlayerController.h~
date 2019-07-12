#pragma once

#include "GameFramework/PlayerController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "I/ITUController.h"
#include "TUPlayerController.generated.h"

UCLASS()
class ATUPlayerController 
: public APlayerController
, public ITUController
{
	GENERATED_BODY()

public:
	ATUPlayerController();

	// ~ITUController Begin
	virtual void PawnBeginPlayEnded_Implementation() override;
	// ~ITUController End
	
	virtual void SetupInputComponent() override;


	/**
	* Sets the new game input enabled state (true - will be processed)
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetGameInputEnableState(bool bInEnabled);

	UFUNCTION(BlueprintPure, Category = Input)
	bool IsGameInputAllowed() const { return bGameInputAllowed; }

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetTUPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetMyTUPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetMyTUPawnChecked() const;
	// ~Access helpers End
	
protected:
	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_LookPitch(float InValue);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_LookYaw(float InValue);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_Forward(float InValue);

	UFUNCTION(Exec, Category = Motions)
	virtual void Axis_Right(float InValue);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_Up(float InValue);

	UFUNCTION(Exec, Category = Use)
	virtual void Action_Use();

	UFUNCTION(Exec, Category = Use)
	virtual void Action_UseTwo();

	UFUNCTION(Exec, Category = Use)
	virtual void Action_UseThree();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_Fire();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_FireTwo();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_FireThree();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectZero();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectOne();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectTwo();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectThree();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectFour();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectFive();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectSix();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectSeven();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectEight();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectNine();

	UFUNCTION(Exec, Category = Menu)
	virtual void Action_OpenGameMenu();

	UFUNCTION(Exec, Category = Menu)
	virtual void Action_CloseGameMenu();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugOne();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugTwo();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugThree();

	/**
	* Returns true if game input actions are to be processed.
	* @note: overload.
	*/
	virtual bool ShouldProcessGameInput() const;

	virtual void ActionMoveGeneral(const FVector& InDirection, float InAmount);
	virtual void ActionSelectGeneral(int32 InIndex);

private:
	// ~Actions Begin
	bool ShouldProcessGameInputLogged(const TCHAR* InSender) const;
	APawn* GetPawnIfShouldInGameContextLogged(const TCHAR* InSender) const;
	
	void Axis_LookPitchChecked(float InValue);
	void Axis_LookYawChecked(float InValue);

	void Axis_ForwardChecked(float InValue);
	void Axis_RightChecked(float InValue);
	void Axis_UpChecked(float InValue);

	void Action_UseChecked();
	void Action_UseTwoChecked();
	void Action_UseThreeChecked();

	void Action_FireChecked();
	void Action_FireTwoChecked();
	void Action_FireThreeChecked();

	void Action_SelectZeroChecked();
	void Action_SelectOneChecked();
	void Action_SelectTwoChecked();
	void Action_SelectThreeChecked();
	void Action_SelectFourChecked();
	void Action_SelectFiveChecked();
	void Action_SelectSixChecked();
	void Action_SelectSevenChecked();
	void Action_SelectEightChecked();
	void Action_SelectNineChecked();

	void ActionSelectGeneralChecked(int32 InIndex);
	// ~Actions End

	UPROPERTY(VisibleInstanceOnly, Category = Input)
	bool bGameInputAllowed = true;
};
