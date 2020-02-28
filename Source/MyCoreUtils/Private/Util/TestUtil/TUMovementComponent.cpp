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

float UTUMovementComponent::SlideAlongSurface(const FVector& Delta, float const Time, const FVector& Normal, FHitResult &Hit, bool const bHandleImpact)
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

void UTUMovementComponent::AddRadialForce(const FVector& Origin, float const Radius, float const Strength, ERadialImpulseFalloff const Falloff)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Origin"), Origin);
	ULogUtilLib::LogFloatC(TEXT("Radius"), Radius);
	ULogUtilLib::LogFloatC(TEXT("Strength"), Strength);
	UPhysUtilLib::LogRadialImpulseFalloffC(TEXT("Falloff"), Falloff);
	Super::AddRadialForce(Origin, Radius, Strength, Falloff);
}

void UTUMovementComponent::AddRadialImpulse(const FVector& Origin, float const Radius, float const Strength, ERadialImpulseFalloff const Falloff, bool const bVelChange)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Origin"), Origin);
	ULogUtilLib::LogFloatC(TEXT("Radius"), Radius);
	ULogUtilLib::LogFloatC(TEXT("Strength"), Strength);
	UPhysUtilLib::LogRadialImpulseFalloffC(TEXT("Falloff"), Falloff);
	ULogUtilLib::LogYesNoC(TEXT("bVelChange"), bVelChange);
	Super::AddRadialImpulse(Origin, Radius, Strength, Falloff, bVelChange);
}

/**
* Set the plane constraint axis setting.
* Changing this setting will modify the current value of PlaneConstraintNormal.
* 
* @param  NewAxisSetting New plane constraint axis setting.
*/
void UTUMovementComponent::SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting const NewAxisSetting)
{
	M_LOGFUNC();
	UPhysUtilLib::LogPlaneConstraintAxisSettingC(TEXT("NewAxisSetting"), NewAxisSetting);
	Super::SetPlaneConstraintAxisSetting(NewAxisSetting);
}

/**
* Sets the normal of the plane that constrains movement, enforced if the plane constraint is enabled.
* Changing the normal automatically sets PlaneConstraintAxisSetting to "Custom".
*
* @param PlaneNormal	The normal of the plane. If non-zero in length, it will be normalized.
*/
void UTUMovementComponent::SetPlaneConstraintNormal(FVector const PlaneNormal)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("PlaneNormal"), PlaneNormal);
	Super::SetPlaneConstraintNormal(PlaneNormal);
}


/** Uses the Forward and Up vectors to compute the plane that constrains movement, enforced if the plane constraint is enabled. */
void UTUMovementComponent::SetPlaneConstraintFromVectors(FVector const Forward, FVector const Up)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Forward"), Forward);
	ULogUtilLib::LogVectorC(TEXT("Up"), Up);
	Super::SetPlaneConstraintFromVectors(Forward, Up);
}


/** Sets the origin of the plane that constrains movement, enforced if the plane constraint is enabled. */
void UTUMovementComponent::SetPlaneConstraintOrigin(FVector const PlaneOrigin)
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("PlaneOrigin"), PlaneOrigin);
	Super::SetPlaneConstraintOrigin(PlaneOrigin);
}


/** Sets whether or not the plane constraint is enabled. */
void UTUMovementComponent::SetPlaneConstraintEnabled(bool const bEnabled)
{
	M_LOGFUNC();
	ULogUtilLib::LogYesNoC(TEXT("bEnabled"), bEnabled);
	Super::SetPlaneConstraintEnabled(bEnabled);
}


/**
* Constrain a direction vector to the plane constraint, if enabled.
* @see SetPlaneConstraint
*/
FVector UTUMovementComponent::ConstrainDirectionToPlane(FVector const Direction) const
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Direction"), Direction);
	FVector const ConstraintedDirection = Super::ConstrainDirectionToPlane(Direction);
	return ConstraintedDirection;
}


/** Constrain a position vector to the plane constraint, if enabled. */
FVector UTUMovementComponent::ConstrainLocationToPlane(FVector const Location) const
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Location"), Location);
	FVector const ConstraintedLocation = Super::ConstrainLocationToPlane(Location);
	return ConstraintedLocation;
}


/** Constrain a normal vector (of unit length) to the plane constraint, if enabled. */
FVector UTUMovementComponent::ConstrainNormalToPlane(FVector const Normal) const
{
	M_LOGFUNC();
	ULogUtilLib::LogVectorC(TEXT("Normal"), Normal);
	FVector const ConstraintedNormal = Super::ConstrainNormalToPlane(Normal);
	return ConstraintedNormal;
}


/** Snap the updated component to the plane constraint, if enabled. */
void UTUMovementComponent::SnapUpdatedComponentToPlane()
{
	M_LOGFUNC();
	Super::SnapUpdatedComponentToPlane();
}


/** Called by owning Actor upon successful teleport from AActor::TeleportTo(). */
void UTUMovementComponent::OnTeleported()
{
	M_LOGFUNC();
	Super::OnTeleported();
}

void UTUMovementComponent::SetTUFlags(ETUFlags const InTUFlags)
{
	TUConfig.SetFlags(InTUFlags);
}
void UTUMovementComponent::UnsetTUFlags(ETUFlags const InFlagMask)
{
	TUConfig.UnsetFlags(InFlagMask);
}
bool UTUMovementComponent::HasAnyTUFlags(ETUFlags const InFlagMask) const
{
	return TUConfig.HasAnyFlags(InFlagMask);
}

bool UTUMovementComponent::HasAllTUFlags(ETUFlags const InFlagMask) const
{
	return TUConfig.HasAllFlags(InFlagMask);
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
