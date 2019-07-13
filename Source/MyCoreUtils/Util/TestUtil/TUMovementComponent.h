#pragma once

#include "GameFramework/MovementComponent.h"
#include "TUTypes.h"
#include "TUMovementComponent.generated.h"

UCLASS()
class UTUMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	UTUMovementComponent();

	virtual void OnRegister() override;

	virtual void StopMovementImmediately() override;

	virtual void PhysicsVolumeChanged(class APhysicsVolume* NewVolume) override;

	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice=0.f, const FVector& MoveDelta = FVector::ZeroVector) override;

	// ~Config Begin
	UFUNCTION(BlueprintPure, Category = "Config")
	ETUFlags GetTUFlags() const { return TUFlags; }

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
	ETUFlags TUFlags;
};
