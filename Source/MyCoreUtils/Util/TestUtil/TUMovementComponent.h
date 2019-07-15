#pragma once

#include "GameFramework/MovementComponent.h"
#include "TUTypes.h"
#include "TUMovementComponent.generated.h"

UCLASS(ClassGroup=(Movement), Meta=(BlueprintSpawnableComponent))
class UTUMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	UTUMovementComponent();

	virtual void OnRegister() override;

	virtual void StopMovementImmediately() override;

	virtual void PhysicsVolumeChanged(class APhysicsVolume* NewVolume) override;

	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice=0.f, const FVector& MoveDelta = FVector::ZeroVector) override;

	/** Update ComponentVelocity of UpdatedComponent. This needs to be called by derived classes at the end of an update whenever Velocity has changed.	 */
	virtual void UpdateComponentVelocity() override;

	/** Initialize collision params appropriately based on our collision settings. Use this before any Line, Overlap, or Sweep tests. */
	virtual void InitCollisionParams(FCollisionQueryParams &OutParams, FCollisionResponseParams& OutResponseParam) const override;

	/** Return true if the given collision shape overlaps other geometry at the given location and rotation. The collision params are set by InitCollisionParams(). */
	virtual bool OverlapTest(const FVector& Location, const FQuat& RotationQuat, const ECollisionChannel CollisionChannel, const FCollisionShape& CollisionShape, const AActor* IgnoreActor) const override;

	/**
	 * Calculate a movement adjustment to try to move out of a penetration from a failed move.
	 * @param Hit the result of the failed move
	 * @return The adjustment to use after a failed move, or a zero vector if no attempt should be made.
	 */
	virtual FVector GetPenetrationAdjustment(const FHitResult& Hit) const override;
	
protected:

	/**
	 * Try to move out of penetration in an object after a failed move. This function should respect the plane constraint if applicable.
	 * @note This simply calls the virtual ResolvePenetrationImpl() which can be overridden to implement custom behavior.
	 * @note The overload taking rotation as an FQuat is slightly faster than the version using FRotator (which will be converted to an FQuat)..
	 * @param Adjustment	The requested adjustment, usually from GetPenetrationAdjustment()
	 * @param Hit			The result of the failed move
	 * @return True if the adjustment was successful and the original move should be retried, or false if no repeated attempt should be made.
	 */
	virtual bool ResolvePenetrationImpl(const FVector& Adjustment, const FHitResult& Hit, const FQuat& NewRotation) override;

public:

	/**
	 * Compute a vector to slide along a surface, given an attempted move, time, and normal.
	 * @param Delta:	Attempted move.
	 * @param Time:		Amount of move to apply (between 0 and 1).
	 * @param Normal:	Normal opposed to movement. Not necessarily equal to Hit.Normal.
	 * @param Hit:		HitResult of the move that resulted in the slide.
	 */
	virtual FVector ComputeSlideVector(const FVector& Delta, const float Time, const FVector& Normal, const FHitResult& Hit) const override;

	/**
	 * Slide smoothly along a surface, and slide away from multiple impacts using TwoWallAdjust if necessary. Calls HandleImpact for each surface hit, if requested.
	 * Uses SafeMoveUpdatedComponent() for movement, and ComputeSlideVector() to determine the slide direction.
	 * @param Delta:	Attempted movement vector.
	 * @param Time:		Percent of Delta to apply (between 0 and 1). Usually equal to the remaining time after a collision: (1.0 - Hit.Time).
	 * @param Normal:	Normal opposing movement, along which we will slide.
	 * @param Hit:		[In] HitResult of the attempted move that resulted in the impact triggering the slide. [Out] HitResult of last attempted move.
	 * @param bHandleImpact:	Whether to call HandleImpact on each hit.
	 * @return The percentage of requested distance (Delta * Percent) actually applied (between 0 and 1). 0 if no movement occurred, non-zero if movement occurred.
	 */
	virtual float SlideAlongSurface(const FVector& Delta, float Time, const FVector& Normal, FHitResult &Hit, bool bHandleImpact = false) override;

	/**
	 * Compute a movement direction when contacting two surfaces.
	 * @param Delta:		[In] Amount of move attempted before impact. [Out] Computed adjustment based on impacts.
	 * @param Hit:			Impact from last attempted move
	 * @param OldHitNormal:	Normal of impact before last attempted move
	 * @return Result in Delta that is the direction to move when contacting two surfaces.
	 */
	virtual void TwoWallAdjust(FVector &Delta, const FHitResult& Hit, const FVector &OldHitNormal) const override;

	/**
	 * Adds force from radial force components.
	 * Intended to be overridden by subclasses; default implementation does nothing.
	 * @param	Origin		The origin of the force
	 * @param	Radius		The radius in which the force will be applied
	 * @param	Strength	The strength of the force
	 * @param	Falloff		The falloff from the force's origin
	 */
	virtual void AddRadialForce(const FVector& Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff) override;

	/**
	 * Adds impulse from radial force components.
	 * Intended to be overridden by subclasses; default implementation does nothing.
	 * @param	Origin		The origin of the force
	 * @param	Radius		The radius in which the force will be applied
	 * @param	Strength	The strength of the force
	 * @param	Falloff		The falloff from the force's origin
	 * @param	bVelChange	If true, the Strength is taken as a change in velocity instead of an impulse (ie. mass will have no effect).
	 */
	virtual void AddRadialImpulse(const FVector& Origin, float Radius, float Strength, ERadialImpulseFalloff Falloff, bool bVelChange) override;

	/**
	 * Set the plane constraint axis setting.
	 * Changing this setting will modify the current value of PlaneConstraintNormal.
	 * 
	 * @param  NewAxisSetting New plane constraint axis setting.
	 */
	virtual void SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting NewAxisSetting) override;

	/**
	 * Sets the normal of the plane that constrains movement, enforced if the plane constraint is enabled.
	 * Changing the normal automatically sets PlaneConstraintAxisSetting to "Custom".
	 *
	 * @param PlaneNormal	The normal of the plane. If non-zero in length, it will be normalized.
	 */
	virtual void SetPlaneConstraintNormal(FVector PlaneNormal) override;

	/** Uses the Forward and Up vectors to compute the plane that constrains movement, enforced if the plane constraint is enabled. */
	virtual void SetPlaneConstraintFromVectors(FVector Forward, FVector Up) override;

	/** Sets the origin of the plane that constrains movement, enforced if the plane constraint is enabled. */
	virtual void SetPlaneConstraintOrigin(FVector PlaneOrigin) override;
	
	/** Sets whether or not the plane constraint is enabled. */
	virtual void SetPlaneConstraintEnabled(bool bEnabled) override;
	/**
	 * Constrain a direction vector to the plane constraint, if enabled.
	 * @see SetPlaneConstraint
	 */
	virtual FVector ConstrainDirectionToPlane(FVector Direction) const override;

	/** Constrain a position vector to the plane constraint, if enabled. */
	virtual FVector ConstrainLocationToPlane(FVector Location) const override;

	/** Constrain a normal vector (of unit length) to the plane constraint, if enabled. */
	virtual FVector ConstrainNormalToPlane(FVector Normal) const override;

	/** Snap the updated component to the plane constraint, if enabled. */
	virtual void SnapUpdatedComponentToPlane() override;

	/** Called by owning Actor upon successful teleport from AActor::TeleportTo(). */
	virtual void OnTeleported() override;

	// ~Config Begin
	UFUNCTION(BlueprintPure, Category = "Config")
	ETUFlags GetTUFlags() const { return TUConfig.GetFlags(); }

	/**
	* Sets flags (and KEEPS old!)
	*/
	UFUNCTION(BlueprintCallable, Category = "Config")
	void SetTUFlags(ETUFlags InFlagMask);

	/**
	* Unsets the given set of flags.
	*/
	UFUNCTION(BlueprintCallable, Category = "Config")
	void UnsetTUFlags(ETUFlags InFlagMask);

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAnyTUFlags(ETUFlags InFlagMask) const;

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAllTUFlags(ETUFlags InFlagMask) const;

	UFUNCTION(BlueprintCallable)
	void LogTUFlags();
	// ~Config End

	// ~Log Begin
	UFUNCTION(BlueprintCallable)
	void LogThis();

	UFUNCTION(BlueprintCallable)
	void LogThisIf(bool bInShouldLog);
	// ~Log End

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Meta=(AllowPrivateAccess = true))
	FTUConfig TUConfig;
};
