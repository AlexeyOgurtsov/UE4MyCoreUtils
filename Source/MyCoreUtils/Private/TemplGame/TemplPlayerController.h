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

private:
};
