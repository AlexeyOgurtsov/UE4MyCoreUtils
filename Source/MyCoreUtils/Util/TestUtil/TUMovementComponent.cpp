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
	ULogUtilLib::LogVectorC(TEXT("MoveDelta"), MoveDelta);
}
void UTUMovementComponent::UpdateComponentVelocity()
{
	M_LOGFUNC();
	Super::UpdateComponentVelocity();
}

void UTUMovementComponent::InitCollisionParams(FCollisionQueryParams &OutParams, FCollisionResponseParams& OutResponseParam) const
{
	M_LOGFUNC();
	Super::InitCollisionParams(OutParams, OutResponseParam);
	UPhysUtilLib::LogCollisionQueryParams(OutParams);
	UPhysUtilLib::LogCollisionResponseParams(OutResponseParam);
}
bool UTUMovementComponent::OverlapTest(const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor) const
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Location"), Location);
	ULogUtilLib::LogQuatC(TEXT("RotationQuat"), RotationQuat);
	UPhysUtilLib::LogCollisionChannelC(TEXT("CollisionChannel"), CollisionChannel);
	UPhysUtilLib::LogCollisionShape(TEXT("CollisionShape"), CollisionShape);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("IgnoreActor"), IgnoreActor);
	bool const bOverlaps = Super::OverlapTest(Location, RotationQuat, CollisionChannel, CollisionShape, IgnoreActor);
	return bOverlaps;
}

FVector UTUMovementComponent::GetPenetrationAdjustment(const FHitResult& Hit) const
{
	M_LOGFUNC();
	UPhysUtilLib::LogHitResult(Hit);
	FVector const Adjustment = Super::GetPenetrationAdjustment(Hit);
	return Adjustment;
}

bool UTUMovementComponent::ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Adjustment"), Adjustment);
	ULogUtilLib::LogQuatC(TEXT("NewRotation"), NewRotation);
	UPhysUtilLib::LogHitResult(Hit);
	bool const bAdjustmentSuccessful = Super::ResolvePenetrationImpl(Adjustment, Hit, NewRotation);
	return bAdjustmentSuccessful;
}


FVector UTUMovementComponent::ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Delta"), Delta);
	ULogUtilLib::LogFloatC(TEXT("Time"), Time);
	ULogUtilLib::LogVectorC(TEXT("Normal"), Normal);
	UPhysUtilLib::LogHitResult(Hit);
	FVector const SlideVector = Super::ComputeSlideVector(Delta, Time, Normal, Hit);
	return SlideVector;
}

float UTUMovementComponent::SlideAlongSurface(const FVector& Delta, float Time, const FVector& Normal, FHitResult &Hit, bool bHandleImpact)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Delta"), Delta);
	ULogUtilLib::LogFloatC(TEXT("Time"), Time);
	ULogUtilLib::LogVectorC(TEXT("Normal"), Normal);
	ULogUtilLib::LogYesNoC(TEXT("bHandleImpact"), bHandleImpact);
	float const DeltaOnPercentApplied = Super::SlideAlongSurface(Delta, Time, Normal, Hit, bHandleImpact);
	UPhysUtilLib::LogHitResult(Hit);
	return DeltaOnPercentApplied;
}

void UTUMovementComponent::TwoWallAdjust(FVector &Delta, const FHitResult& Hit, const FVector &OldHitNormal) const
{
	M_LOGFUNC();
	UPhysUtilLib::LogHitResult(Hit);
	Super::TwoWallAdjust(Delta, Hit, OldHitNormal);
	ULogUtilLib::LogVectorC(TEXT("Delta"), Delta);
	ULogUtilLib::LogVectorC(TEXT("OldHitNormal"),OldHitNormal);
}

void UTUMovementComponent::AddRadialForce(const FVector& Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Origin"), Origin);
	ULogUtilLib::LogFloatC(TEXT("Radius"), Radius);
	ULogUtilLib::LogFloatC(TEXT("Strength"), Strength);
	M_TO_BE_IMPL(TEXT("Falloff log"));
	Super::AddRadialForce(Origin, Radius, Strength, Falloff);
}

void UTUMovementComponent::AddRadialImpulse(const FVector& Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, bool bVelChange)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Origin"), Origin);
	ULogUtilLib::LogFloatC(TEXT("Radius"), Radius);
	ULogUtilLib::LogFloatC(TEXT("Strength"), Strength);
	M_TO_BE_IMPL(TEXT("Falloff log"));
	ULogUtilLib::LogYesNoC(TEXT("bVelChange"), bVelChange);
	Super::AddRadialImpulse(Origin, Radius, Strength, Falloff, bVelChange);
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
