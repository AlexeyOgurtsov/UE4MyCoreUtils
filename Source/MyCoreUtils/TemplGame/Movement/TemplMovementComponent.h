#pragma once

#include "Util/TestUtil/TUMovementComponent.h"
#include "TemplMovementComponent.generated.h"

UCLASS()
class UTemplMovementComponent : public UTUMovementComponent
{
	GENERATED_BODY()

public:
	UTemplMovementComponent();

	virtual void TickComponent(float InDeltaTime, ELevelTick InLevelTick, FComponentTickFunction* InThisTickFunction) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Movement)
	bool TestMoveTick(float InDeltaTime);
};
