#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPlayerController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "TemplPlayerController.generated.h"

class ATemplPawn;

UCLASS()
class ATemplPlayerController : public ATUPlayerController
{
	GENERATED_BODY()

public:
	ATemplPlayerController();

	// ~AActor Begin
	virtual void BeginPlay() override;
	// ~AActor End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATemplPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	ATemplPawn* GetMyPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATemplPawn* GetMyPawnChecked() const;
	// ~Access helpers End

protected:
	// ~Controller-level action handlers Begin
	virtual void Axis_LookPitch(APawn* P, float InAmount) override;
	virtual void Axis_LookYaw(APawn* P, float InAmount) override;
	virtual void Axis_Forward(APawn* P, float InAmount) override;
	virtual void Axis_Right(APawn* P, float InAmount) override;
	virtual void Axis_Up(APawn* P, float InAmount) override;
	virtual void Action_Use() override;
	virtual void Action_UseTwo() override;
	virtual void Action_UseThree() override;
	virtual void Action_Fire() override;
	virtual void Action_FireTwo() override;
	virtual void Action_FireThree() override;
	virtual void Action_SelectZero() override;
	virtual void Action_SelectOne() override;
	virtual void Action_SelectTwo() override;
	virtual void Action_SelectThree() override;
	virtual void Action_SelectFour() override;
	virtual void Action_SelectFive() override;
	virtual void Action_SelectSix() override;
	virtual void Action_SelectSeven() override;
	virtual void Action_SelectEight() override;
	virtual void Action_SelectNine() override;
	virtual void Action_OpenGameMenu() override;
	virtual void Action_CloseGameMenu() override;
	virtual void Action_DebugOne() override;
	virtual void Action_DebugTwo() override;
	virtual void Action_DebugThree() override;
	// ~Controller-level action handlers End

private:
};
