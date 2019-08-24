#include "TUProjectileActor.h"
#include "Util/Core/LogUtilLib.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "UObject/ConstructorHelpers.h"

/**
* TODO:
* 0. Config
* 0.1. Change config
* 0.2. Init default damage type
* 1. Handle collision
* 1.0. Override collision handling method
* 1.1. Stop movement (+DONE)
* 1.2. Make damage (+DONE)
* 1.3. Begin destruction
* 2. Init projectile movement component
* 2.1. Init movement direction
*/

using namespace ProjectileConfig;

ATUProjectileActor::ATUProjectileActor()
{
	RootComponent = RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));

	OnActorHit.AddDynamic(this, &ATUProjectileActor::ActorHit);

	InitCameraAndSpringArm(RootSceneComponent);
	InitMesh(RootSceneComponent);
	InitProxSphere(RootSceneComponent);

	InitProjectileMovementComponent(RootComponent);
}

void ATUProjectileActor::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	MakeImpact(Hit.Actor.Get(), Hit);
}

void ATUProjectileActor::MakeDamage(AActor* const ActorToDamage, const FHitResult& InHitInfo)
{
	if(bPointDamage)
	{
		if(ActorToDamage)
		{
			UGameplayStatics::ApplyPointDamage(ActorToDamage, Damage, GetVelocity(), InHitInfo, GetInstigatorController(), Instigator, DamageTypeClass);
		}
	}	
	else
	{
		TArray<AActor*> IgnoreActors; 
		UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), DamageRadius, DamageTypeClass, IgnoreActors, Instigator, GetInstigatorController());
	}
}


void ATUProjectileActor::MakeImpact(AActor* const ActorToDamage, const FHitResult& InHitInfo)
{
	MakeDamage(ActorToDamage, InHitInfo);


	ProjectileMovementComponent->StopMovementImmediately();

	// TODO: Spawn explosition

	bool bDestroyed = Destroy();
	M_LOG_WARN_IF( ! bDestroyed, TEXT("AActor::Destroy() returned false for '%s'"), *ULogUtilLib::GetNameAndClassSafe(this));
}

void ATUProjectileActor::InitProjectileMovementComponent(USceneComponent* UpdatedComponent)
{
	check(UpdatedComponent);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileMovementComponent->SetUpdatedComponent(UpdatedComponent);

	ProjectileMovementComponent->MaxSpeed = Default::MAX_SPEED;
	ProjectileMovementComponent->InitialSpeed = Default::MAX_SPEED;
	ProjectileMovementComponent->Velocity = UpdatedComponent->GetComponentQuat().Vector();

}

void ATUProjectileActor::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->RelativeRotation = Default::SPRINGARM_RELATIVE_ROTATION;
	SpringArm->RelativeLocation = Default::SPRINGARM_RELATIVE_LOCATION;
	SpringArm->bEnableCameraLag = Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = Default::SPRINGARM_CAMERA_LAG_SPEED;
	SpringArm->SetupAttachment(InAttachTo);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATUProjectileActor::InitMesh(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("Default mesh (\"%s\") NOT found"), Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("Default mesh (\"%s\") found, setting it up"), Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
		}

		Mesh->SetupAttachment(InAttachTo);
	}
}

void ATUProjectileActor::InitProxSphere(USceneComponent* InAttachTo)
{
	checkf(InAttachTo, TEXT("When calling %s component to attach to must be non-NULL pointer"), TEXT(__FUNCTION__));

	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(Default::PROX_SPHERE_RADIUS);
	ProxSphere->RelativeLocation = Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION;
	ProxSphere->SetupAttachment(InAttachTo);
}
