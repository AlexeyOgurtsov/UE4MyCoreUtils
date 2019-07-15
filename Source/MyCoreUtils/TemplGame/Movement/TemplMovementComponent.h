#pragma once

#include "Util/TestUtil/TUMovementComponent.h"
#include "TemplMovementComponent.generated.h"

UCLASS(ClassGroup=(Movement), Meta=(BlueprintSpawnableComponent))
class UTemplMovementComponent : public UTUMovementComponent
{
	GENERATED_BODY()

public:
	UTemplMovementComponent();

	virtual void TickComponent(float InDeltaTime, ELevelTick InLevelTick, FActorComponentTickFunction* InThisTickFunction) override;

protected:
	UFUNCTION(BlueprintCallable, Category = Movement)
	bool TestMoveTick(float InDeltaTime);
};
