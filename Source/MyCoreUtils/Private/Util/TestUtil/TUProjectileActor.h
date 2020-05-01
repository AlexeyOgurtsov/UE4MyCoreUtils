#pragma once

/**
* Actor that has collision and mesh.
*/

#include "TUActor.h"
#include "ProjectileConfig.h"
#include "TUProjectileConfigProps.h"
#include "TUProjectileActor.generated.h"

class USoundBase;
class UProjectileMovementComponent;
class UCameraComponent;
class USpringArmComponent;
class USceneComponent;
class UStaticMeshComponent;
class USphereComponent;
class UDamageType;
class UAudioComponent;

UCLASS()
class ATUProjectileActor : public ATUActor
{
	GENERATED_BODY()

public:
	ATUProjectileActor();

	/** BeginPlay*/
	UFUNCTION(BlueprintCallable, Category=Misc)
	void BeginPlay() override;

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
	
	/** GetFlySound*/
	UFUNCTION(BlueprintPure, Category=Sound)
	UAudioComponent* GetFlySound() const
	{
		return FlySound;
	}
	
	/** GetConfigProps*/
	UFUNCTION(BlueprintPure, Category=Config)
	const FTUProjectileConfigProps& GetConfigProps() const
	{
		return ConfigProps;
	}
	
private:
	/** ConfigProps*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Config)
	FTUProjectileConfigProps ConfigProps;

	// ~ Sound Begin
	/** FlySound*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Sound)
	UAudioComponent* FlySound = nullptr;

	void InitAudio(USceneComponent* InParentComponent);
	void StartFlyAudio();
	// ~ Sound End

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

	// ~Destruction Begin
	UFUNCTION(BlueprintCallable, Category = Destruction)
	void SetShouldPreventDestructionOnHit(bool bInValue = true) { bPreventDestructionOnHit = bInValue; }

	UFUNCTION(BlueprintPure, Category = Destruction)
	bool ShouldPreventDestructionOnHit() const { return bPreventDestructionOnHit; }
	// ~Destruction End

	// ~ Movement Begin
	/** ProjectileMovementComponent*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Meta=(AllowPrivateAccess=true), Category=Movement)
	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;

	/** ActorHit*/	
	UFUNCTION(Category=Collision)
	void ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
	
	/** InitProjectileMovementComponent*/
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

	// ~ Destruction Begin 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Destruction, Meta=(AllowPrivateAccess=true))
	bool bPreventDestructionOnHit = false;
	// ~ Destruction End
};

// ~ RightHere_ATUProjectileActor Begin


// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_ATUProjectileActor End
