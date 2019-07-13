#include "TUMovementComponent.h"
#include "TUTypesLib.h"
#include "Util/Core/Phys/PhysUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "GameFramework/Actor.h"

UTUMovementComponent::UTUMovementComponent()
{
}
void UTUMovementComponent::OnRegister()
{
	M_LOGFUNC();
	LogThis();

	Super::OnRegister();

}

void UTUMovementComponent::StopMovementImmediately()
{
	M_LOGFUNC();
	LogThis();

	Super::StopMovementImmediately();
}

void UTUMovementComponent::PhysicsVolumeChanged(class APhysicsVolume* const NewVolume)
{
	M_LOGFUNC();
	LogThis();

	Super::PhysicsVolumeChanged(NewVolume);
}

void UTUMovementComponent::HandleImpact(const FHitResult& Hit, float const TimeSlice, const FVector& MoveDelta)
{
	M_LOGFUNC();
	LogThis();

	Super::HandleImpact(Hit, TimeSlice, MoveDelta);
	UPhysUtilLib::LogHitResult(Hit);
	ULogUtilLib::LogFloatC(TEXT("TimeSlice"), TimeSlice);
	ULogUtilLib::LogStringC(TEXT("MoveDelta"), MoveDelta.ToString());
}

void UTUMovementComponent::SetTUFlags(ETUFlags const InTUFlags)
{
	LogTUFlags();
	TUFlags |= InTUFlags;
	M_LOG(TEXT("New flags:"));
	LogTUFlags();
}
void UTUMovementComponent::UnsetTUFlags(ETUFlags const InFlagMask)
{
	LogTUFlags();
	TUFlags &= ~InFlagMask;
	M_LOG(TEXT("New flags:"));
	LogTUFlags();
}
bool UTUMovementComponent::HasAnyTUFlags(ETUFlags const InFlagMask) const
{
	return ((TUFlags & InFlagMask) != ETUFlags::None);
}

bool UTUMovementComponent::HasAllTUFlags(ETUFlags const InFlagMask) const
{
	return ((TUFlags & InFlagMask) == InFlagMask);
}

void UTUMovementComponent::LogTUFlags()
{
	LogThis();
	UTUTypesLib::LogTUFlags(GetTUFlags());
}
void UTUMovementComponent::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("UpdatedComponent"), UpdatedComponent);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Owner actor"), UpdatedComponent ? UpdatedComponent->GetOwner() : nullptr);
}

void UTUMovementComponent::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}
