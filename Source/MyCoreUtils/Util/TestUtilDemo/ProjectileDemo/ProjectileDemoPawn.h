#pragma once

/**
* To be copied to the destination and changed.
*/

#include "ProjectileDemoTypes.h"
#include "ProjectileDemoPawnBase.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "ProjectileDemoPawn.generated.h"

class ATUProjectileActor;

UCLASS()
class AProjectileDemoPawn : public AProjectileDemoPawnBase
{
	GENERATED_BODY()

	// ~Framework Begin
	virtual void MyBeginPlay_Implementation() override;
	// ~Framework End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Controller)
	AProjectileDemoPlayerController* GetMyPC() const;

	UFUNCTION(BlueprintPure, Category = Controller)
	AProjectileDemoPlayerController* GetMyPCLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Controller)
	AProjectileDemoPlayerController* GetMyPCChecked() const;
	// ~Access helpers End

public:
	AProjectileDemoPawn();

	/** LogDirection*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void LogDirection();
	
	// ~ Projectile Begin
	/** LaunchProjectile*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	ATUProjectileActor* LaunchProjectile();

	/** LaunchProjectileGeneral*/
	UFUNCTION(BlueprintCallable, Category=Weapon)
	ATUProjectileActor* LaunchProjectileGeneral(const FTransform& InTransform, TSubclassOf<ATUProjectileActor> InClass);
	
	/** GetProjectileLaunchTransform*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	FTransform GetProjectileLaunchTransform() const;
	
	/** GetProjectileClass*/
	UFUNCTION(BlueprintPure, Category=Weapon)
	TSubclassOf<ATUProjectileActor> GetProjectileClass() const
	{
		return ProjectileClass;
	}
	
	/** ProjectileClass*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Weapon)
	TSubclassOf<ATUProjectileActor> ProjectileClass;
	
	/** ProjectileSettings*/
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Weapon)
	FProjectileDemo_ProjectileSettings ProjectileSettings;
	
	// ~ Projectile End
	/** GetProjectileSettings*/
	//UFUNCTION(BlueprintPure, Category=Weapon)
	//FProjectileDemo_ProjectileSettings GetProjectileSettings() const
	//{
	//	return ProjectileSettings;
	//}
	
private:
	// ~Motion Begin
	void InitMovement();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Motion, Meta=(AllowPrivateAccess = true))
	UPawnMovementComponent *Movement = nullptr;
	// ~Motion End
};
