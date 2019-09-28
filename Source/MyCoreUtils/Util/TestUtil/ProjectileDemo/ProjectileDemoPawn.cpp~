#include "ProjectileDemoPawn.h"
#include "ProjectileDemoPlayerController.h"
#include "ProjectileDemoConfig.h"
#include "Util/TestUtil/TUProjectileActor.h"

#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"
#include "GameFramework/FloatingPawnMovement.h"

/**
* TODO Fix: Movement
* 1. Floating pawn movement: does it work by default (seems like not)?
*/

namespace
{
	namespace Config
	{
		constexpr float MAX_SPEED = 100.0F;
		constexpr float ACCELERATION = 0.0F;
		constexpr float DECELERATION = 0.0F;
	} // Config
} // anonymous

MyPawnType::AProjectileDemoPawn()
{
	ProjectileClass = ATUProjectileActor::StaticClass();

	InitMovement();
}
void MyPawnType::MyBeginPlay_Implementation()
{
	M_LOGFUNC();

	Super::MyBeginPlay_Implementation();
	// Custom actions here
}

void MyPawnType::LogDirection()
{
	ULogUtilLib::LogRotatorC(TEXT("ActorRotation"), GetActorRotation());
	ULogUtilLib::LogVectorC(TEXT("ActorRotation.Vector()"), GetActorRotation().Vector());
	ULogUtilLib::LogRotatorC(TEXT("ControlRotation"), GetControlRotation());
}

ATUProjectileActor* MyPawnType::LaunchProjectile()
{
	FTransform const SpawnTransform = GetProjectileLaunchTransform();
	ATUProjectileActor* const NewActor = LaunchProjectileGeneral(SpawnTransform, ProjectileClass);
	return NewActor;
}

ATUProjectileActor* MyPawnType::LaunchProjectileGeneral(const FTransform& InTransform, TSubclassOf<ATUProjectileActor> InClass)
{
	LogDirection();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	ATUProjectileActor* const NewActor = GetWorld()->SpawnActor<ATUProjectileActor>(ATUProjectileActor::StaticClass(), InTransform, SpawnParams);
	return NewActor;
}

FTransform MyPawnType::GetProjectileLaunchTransform() const
{
	//FRotator const LaunchRotation = GetActorRotation();
	//FVector const LaunchLocation = GetActorLocation() + LaunchRotation.Vector() * ProjectileSettings.LaunchShift; 
	
	FVector EyeLocation;
	FRotator EyeRotation;
	GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FRotator const LaunchRotation = EyeRotation;
	FVector const LaunchLocation = EyeLocation + LaunchRotation.Vector() * ProjectileSettings.LaunchShift; 
	
	ULogUtilLib::LogRotatorC(TEXT("LaunchRotation"), LaunchRotation);
	ULogUtilLib::LogVectorC(TEXT("LaunchLocation"), LaunchLocation);

	return FTransform{ LaunchRotation, LaunchLocation, FVector::OneVector };
}

void MyPawnType::InitMovement()
{
	M_LOGFUNC();
	UFloatingPawnMovement* const MyMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	MyMovement->Acceleration = Config::ACCELERATION;
	MyMovement->Deceleration = Config::DECELERATION;
	MyMovement->MaxSpeed = Config::MAX_SPEED;
	Movement = MyMovement;
}

MyPCType* MyPawnType::GetMyPC() const
{
	return Cast<MyPCType>(GetController());
}

MyPCType* MyPawnType::GetMyPCLogged(ELogFlags InLogFlags) const
{
	MyPCType* const PC = GetMyPC();
	if(PC == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPC() returned NULL"));
	}
	return PC;
}

MyPCType* MyPawnType::GetMyPCChecked() const
{
	MyPCType* const PC = GetMyPC();
	checkf(PC, TEXT("GetMyPawn must return non-NULL pawn!"));
	return PC;
}
