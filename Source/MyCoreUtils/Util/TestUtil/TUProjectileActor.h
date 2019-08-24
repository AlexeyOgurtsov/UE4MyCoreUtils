#pragma once

/**
* Actor that has collision and mesh.
*/

#include "TUActor.h"
#include "ProjectileConfig.h"
#include "TUProjectileActor.generated.h"

class UProjectileMovementComponent;
class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class UDamageType;

UCLASS()
class ATUProjectileActor : public ATUActor
{
	GENERATED_BODY()

public:
	ATUProjectileActor();

	UFUNCTION(BlueprintPure, Category = Components)
	USceneComponent* GetRootSceneComponent() const { return RootSceneComponent; }

	UFUNCTION(BlueprintPure, Category = Camera)
	UCameraComponent* GetCamera() const { return Camera; }

	UFUNCTION(BlueprintPure, Category = Visual)
	UStaticMeshComponent* GetMesh() const { return Mesh; }

	UFUNCTION(BlueprintPure, Category = Collision)
	USphereComponent* GetProxSphere() const { return ProxSphere; }

	// ~ Movement Begin
	/** GetProjectileMovementComponent*/
	UFUNCTION(BlueprintPure, Category=Movement)
	UProjectileMovementComponent* GetProjectileMovementComponent() const
	{
		return ProjectileMovementComponent;
	}
	
	// ~ Movement End
	
	// ~ Damage Begin
	/** GetDamageType*/
	UFUNCTION(BlueprintPure, Category=Damage)
	TSubclassOf<UDamageType> GetDamageTypeClass() const
	{
		return DamageTypeClass;
	}
	
	/** IsPointDamage*/
	UFUNCTION(BlueprintPure, Category=Damage)
	bool IsPointDamage() const
	{
		return bPointDamage;
	}
	
	/** GetDamage*/
	UFUNCTION(BlueprintPure, Category=Damage)
	float GetDamage() const
	{
		return Damage;
	}

	/** GetDamageRadius*/
	UFUNCTION(BlueprintPure, Category=Damage)
	float GetDamageRadius() const
	{
		return DamageRadius;
	}
	
	// ~ Damage End
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Components, Meta=(AllowPrivateAccess = true))
	USceneComponent* RootSceneComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	UCameraComponent* Camera = nullptr;
	void InitCameraAndSpringArm(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera, Meta=(AllowPrivateAccess = true))
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Visual, Meta=(AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh = nullptr;
	void InitMesh(USceneComponent* InAttachTo);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Collision, Meta=(AllowPrivateAccess = true))
	USphereComponent* ProxSphere = nullptr;
	void InitProxSphere(USceneComponent* InAttachTo);

	// ~ Movement Begin
	/** ProjectileMovementComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Movement)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	/** ActorHit*/
	UFUNCTION(Category=Collision)
	void ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	
	/** InitProjectileMovementComponent*/
	UFUNCTION(BlueprintCallable, Category=Movement)
	void InitProjectileMovementComponent(USceneComponent* UpdatedComponent);
	
	// ~ Movement End
	
	// ~ Collision Begin
	// ~ Collision End
	
	// ~ Damage Begin
	/** Damage*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Damage)
	float Damage = ProjectileConfig::Default::DAMAGE;
	
	/** DamageType*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Damage)
	TSubclassOf<UDamageType> DamageTypeClass = nullptr;

	/** DamageRadius*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Damage)
	float DamageRadius = ProjectileConfig::Default::DAMAGE_RADIUS;
	
	/** bPointDamage*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Damage)
	bool bPointDamage = false;
	
	/** MakeImpact*/
	UFUNCTION(BlueprintCallable, Category=Damage)
	void MakeImpact(AActor* ActorToDamage, const FHitResult& InHitInfo);
	
	/** MakeDamage*/
	UFUNCTION(BlueprintCallable, Category=Damage)
	void MakeDamage(AActor* ActorToDamage, const FHitResult& InHitInfo);
	// ~ Damage End
};
