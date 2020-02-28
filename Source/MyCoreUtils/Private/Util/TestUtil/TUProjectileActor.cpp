#include "TUProjectileActor.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Core/Phys/PhysUtilLib.h"
#include "Util/Audio/AudioUtilLib.h"

#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/AudioComponent.h"

#include "UObject/ConstructorHelpers.h"

#include "Engine/CollisionProfile.h"

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
*/

using namespace ProjectileConfig;

ATUProjectileActor::ATUProjectileActor()
{
	OnActorHit.AddDynamic(this, &ATUProjectileActor::ActorHit);

	InitMesh(nullptr);
	RootComponent = Mesh;
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
	RootSceneComponent->SetupAttachment(RootComponent);

	InitCameraAndSpringArm(RootSceneComponent);
	InitProxSphere(RootSceneComponent);
	InitProjectileMovementComponent(RootComponent);
	InitAudio(RootSceneComponent);
	
}

void ATUProjectileActor::BeginPlay()
{
	M_LOGFUNC();
	Super::BeginPlay();
	SetLifeSpan(ProjectileConfig::Default::MAX_LIFETIME_SECONDS);
	StartFlyAudio();
}

void ATUProjectileActor::StartFlyAudio()
{
	UAudioUtilLib::SetAudioComponentFromMySoundMultiplier(FlySound, ConfigProps.Audio.FlyMultiplier);
	FlySound->Play();
}

void ATUProjectileActor::ActorHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	M_LOGFUNC();

	UAudioUtilLib::PlayMySoundAtLocationIfShould(this, ConfigProps.Audio.HitSound, Hit.Location, FRotator::ZeroRotator);

	MakeImpact(Hit.Actor.Get(), Hit);
}

void ATUProjectileActor::MakeDamage(AActor* const ActorToDamage, const FHitResult& InHitInfo)
{
	M_LOGFUNC();
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("ActorToDamage"), ActorToDamage);
	UPhysUtilLib::LogHitResult(InHitInfo);

	if(bPointDamage)
	{
		if(ActorToDamage)
		{
			UGameplayStatics::ApplyPointDamage(ActorToDamage, Damage, GetVelocity(), InHitInfo, GetInstigatorController(), GetInstigator(), DamageTypeClass);
		}
	}	
	else
	{
		TArray<AActor*> IgnoreActors; 
		UGameplayStatics::ApplyRadialDamage(this, Damage, GetActorLocation(), DamageRadius, DamageTypeClass, IgnoreActors, GetInstigator(), GetInstigatorController());
	}
}


void ATUProjectileActor::MakeImpact(AActor* const ActorToDamage, const FHitResult& InHitInfo)
{
	M_LOGFUNC();

	MakeDamage(ActorToDamage, InHitInfo);

	ProjectileMovementComponent->StopMovementImmediately();

	// TODO: Spawn explosition

	bool bDestroyed = Destroy();
	M_LOG_WARN_IF( ! bDestroyed, TEXT("AActor::Destroy() returned false for '%s'"), *ULogUtilLib::GetNameAndClassSafe(this));
}

void ATUProjectileActor::InitAudio(USceneComponent* InParentComponent)
{
	M_LOGFUNC();
	FlySound = CreateDefaultSubobject<UAudioComponent>(TEXT("FlySoundComponent"));
	FlySound->bAutoActivate = false;

	if(InParentComponent)
	{
		FlySound->SetupAttachment(InParentComponent);
	}
}

void ATUProjectileActor::InitProjectileMovementComponent(USceneComponent* InUpdatedComponent)
{
	M_LOGFUNC();
	float const INITIAL_SPEED = ProjectileConfig::Default::SPEED;

	check(InUpdatedComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	ProjectileMovementComponent->MaxSpeed = ProjectileConfig::Default::MAX_SPEED;
	ProjectileMovementComponent->InitialSpeed = INITIAL_SPEED;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0F;
	ProjectileMovementComponent->bInitialVelocityInLocalSpace = true;
	ProjectileMovementComponent->Velocity = FVector{INITIAL_SPEED, 0.0F, 0.0F};
}

void ATUProjectileActor::InitCameraAndSpringArm(USceneComponent* InAttachTo)
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->TargetArmLength = ProjectileConfig::Default::SPRINGARM_TARGET_ARM_LENGTH;
	SpringArm->SetRelativeRotation(ProjectileConfig::Default::SPRINGARM_RELATIVE_ROTATION);
	SpringArm->SetRelativeLocation(ProjectileConfig::Default::SPRINGARM_RELATIVE_LOCATION);
	SpringArm->bEnableCameraLag = ProjectileConfig::Default::SPRINGARM_ENABLE_CAMERA_LAG;
	SpringArm->CameraLagSpeed = ProjectileConfig::Default::SPRINGARM_CAMERA_LAG_SPEED;
	if(InAttachTo)
	{
		SpringArm->SetupAttachment(InAttachTo);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = true;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
}

void ATUProjectileActor::InitMesh(USceneComponent* InAttachTo)
{
	static ConstructorHelpers::FObjectFinderOptional<UStaticMesh> MeshFinder { ProjectileConfig::Default::MESH_ASSET_PATH };
	M_LOG_ERROR_IF( ! MeshFinder.Succeeded(), TEXT("ProjectileConfig mesh (\"%s\") NOT found"), ProjectileConfig::Default::MESH_ASSET_PATH);

	{
		Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

		if(MeshFinder.Succeeded())
		{
			M_LOG(TEXT("ProjectileConfig mesh (\"%s\") found, setting it up"), ProjectileConfig::Default::MESH_ASSET_PATH);
			Mesh->SetStaticMesh(MeshFinder.Get());
			Mesh->SetCollisionProfileName(UCollisionProfile::DefaultProjectile_ProfileName);
			Mesh->SetRelativeScale3D(FVector{ProjectileConfig::Default::Scale});
		}

		if(InAttachTo)
		{
			Mesh->SetupAttachment(InAttachTo);
		}
	}
}

void ATUProjectileActor::InitProxSphere(USceneComponent* InAttachTo)
{
	ProxSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	ProxSphere->InitSphereRadius(ProjectileConfig::Default::PROX_SPHERE_RADIUS);
	ProxSphere->SetRelativeLocation(ProjectileConfig::Default::MESH_REAL_CENTER_ACTOR_SPACE_LOCATION);
	if(InAttachTo)
	{
		ProxSphere->SetupAttachment(InAttachTo);
		ProxSphere->SetRelativeScale3D(FVector{ProjectileConfig::Default::Scale});
	}
}
