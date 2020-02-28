#pragma once

/**
* To be copied to the destination and changed.
*/

#include "Util/TestUtil/TUPlayerController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "ProjectileDemoPlayerController.generated.h"

class AProjectileDemoPawn;

UCLASS()
class AProjectileDemoPlayerController : public ATUPlayerController
{
	GENERATED_BODY()

public:
	AProjectileDemoPlayerController();

	// ~AActor Begin
	virtual void BeginPlay() override;
	// ~AActor End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	AProjectileDemoPawn* GetMyPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	AProjectileDemoPawn* GetMyPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	AProjectileDemoPawn* GetMyPawnChecked() const;
	// ~Access helpers End
	
protected:
	virtual void Action_Fire() override;
	virtual void Action_FireTwo() override;
	virtual void Action_FireThree() override;
private:
};
