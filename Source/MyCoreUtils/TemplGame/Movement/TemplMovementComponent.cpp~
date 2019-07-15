#include "TemplMovementComponent.h"
#include "Util/Core/LogUtilLib.h"

namespace
{
	using MyComponentType = UTemplMovementComponent;

	constexpr float TEST_SPEED = 100.0F; // UU / S (Cm / S)
	FVector const TEST_VELOCITY { TEST_SPEED, 0.0F, 0.0F };
} // Anonymous

MyComponentType::UTemplMovementComponent()
{
	Velocity = TEST_VELOCITY;
}

void MyComponentType::TickComponent(float const InDeltaTime, ELevelTick const InLevelTick, FActorComponentTickFunction* const InThisTickFunction)
{
	if(ShouldSkipUpdate(InDeltaTime))
	{
		return;
	}

	Super::TickComponent(InDeltaTime, InLevelTick, InThisTickFunction);

	TestMoveTick(InDeltaTime); M_TO_BE_IMPL(TEXT("Replace TestMoveTick with own code (@see TestMoveTick)"));
}

bool MyComponentType::TestMoveTick(float const InDeltaTime)
{
	checkf(UpdatedComponent, TEXT("%s to be called only when UpdatedComponent is non-NULL"), TEXT(__FUNCTION__));

	FVector const DeltaLocation = InDeltaTime * Velocity;

	FHitResult Hit;
	bool const bCollisionEnabled = true;
	bool const bMoved = MoveUpdatedComponent(DeltaLocation, UpdatedComponent->GetComponentQuat(), bCollisionEnabled, &Hit/*, ETeleportType::None*/);

	return bMoved;
}
