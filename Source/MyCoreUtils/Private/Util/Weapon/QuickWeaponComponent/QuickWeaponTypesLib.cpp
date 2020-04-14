#include "QuickWeaponTypesLib.h"
#include "QuickWeaponComponent.h"
#include "Util/Core/LogUtilLib.h"

#include "Util/Weapon/MyDefaultProjectile.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/StaticMeshSocket.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

bool UQuickWeaponTypesLib::InitializePrimaryWeapon(UQuickWeaponComponent* WeaponComponent, FName InComponentName)
{
	FWeaponSocketConfig SocketConfig;
	{
		SocketConfig.SocketName = PRIMARY_WEAPON_SOCKET_NAME;
	}

	FQuickWeaponConfig PrimaryWeaponConfig;
	{
		PrimaryWeaponConfig.ProjectileClass = AMyDefaultProjectile::StaticClass();
		PrimaryWeaponConfig.MinFireInterval = 1.0F;
	}

	const bool bAdded = AddSocketWithWeapon(WeaponComponent, PRIMARY_WEAPON_NAME, PrimaryWeaponConfig, SocketConfig, InComponentName);
	return bAdded;
}

bool UQuickWeaponTypesLib::AddSocketWithWeapon(UQuickWeaponComponent* WeaponComponent, FName InWeaponName, const FQuickWeaponConfig& InWeapon, const FWeaponSocketConfig& InSocket, FName InComponentName)
{
	//checkf(WeaponComponent, TEXT("Passed weapon component must be valid NON-null pointer"));
	FWeaponComponentConfigRef const ConfigRef {InWeaponName};
	if( ! AddNewWeaponSocket(WeaponComponent->Config, ConfigRef.SocketName, InSocket) )
	{
		return false;
	}
	if( ! AddNewWeapon(WeaponComponent->Config, InWeaponName, InWeapon) )
	{
		return false;
	}
	WeaponComponent->Config.UsedWeaponNames.Add(InWeaponName);
	if( ! SetSocketToWeapon( WeaponComponent->Config, InWeaponName, ConfigRef.SocketName ) )
	{
		return false;
	}
	WeaponComponent->SocketsToAttach.Add(FWeaponComponentSocketRef{ConfigRef, InSocket.SocketName, InComponentName});
	return true;
}

bool UQuickWeaponTypesLib::AddNewWeaponSocket(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, const FName InSocketName, const FWeaponSocketConfig& InSocketConfig)
{
	M_LOGFUNC();
	FWeaponSocketConfig* const Socket = Config.Sockets.Find(InSocketName);
	if(Socket != nullptr)
	{
		M_LOG_ERROR(TEXT("Weapon socket with name \"%s\" already registered"), *InSocketName.ToString());
		return false;
	}
	Config.Sockets.Add(InSocketName, InSocketConfig);
	return true;
}

bool UQuickWeaponTypesLib::AddNewWeapon(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, const FName InWeaponName, const FQuickWeaponConfig& InWeaponConfig)
{
	M_LOGFUNC();
	FQuickWeaponConfig* const Weapon = Config.Weapons.Find(InWeaponName);
	if(Weapon != nullptr)
	{
		M_LOG_ERROR(TEXT("Weapon with name \"%s\" already registered"), *InWeaponName.ToString());
		return false;
	}
	Config.Weapons.Add(InWeaponName, InWeaponConfig);
	return true;
}

bool UQuickWeaponTypesLib::SetSocketToWeapon(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, FName InWeaponName, FName InSocketName)
{
	M_LOGFUNC();
	FName* SocketName = Config.WeaponSocketNames.Find(InWeaponName);
	if(SocketName != nullptr)
	{
		M_LOG_ERROR(TEXT("Weapon with name \"%s\" already binded to socket"), *InWeaponName.ToString());
		return false;
	}
	Config.WeaponSocketNames.Add(InWeaponName, InSocketName);
	return true;
}

void FAttachedWeaponSocket::UpdateFromSocket()
{
	UpdateBaseSocketTransform();
	FTransform const FinalTransform = FTransform{SocketConfig.SocketRotation, SocketConfig.SocketOffset} * BaseSocketTransform;
	LaunchLocation = FinalTransform.GetTranslation();
	LaunchRotator = FinalTransform.Rotator();
}

void FAttachedWeaponSocket::UpdateBaseSocketTransform()
{
	bool bSucceeded = false;
	UStaticMeshComponent* StaticMeshComponent = nullptr;
	USkeletalMeshComponent* SkeletalMeshComponent = nullptr;
	switch(SocketType)
	{
	case EWeaponSocketType::StaticMesh:
		StaticMeshComponent = CastChecked<UStaticMeshComponent>(MeshComponent);
		bSucceeded = StaticMeshSocket->GetSocketTransform(BaseSocketTransform, StaticMeshComponent);
		checkf(bSucceeded, TEXT("UStaticMeshSocket::GetSocketTransform() must succeed!"));
		break;

	case EWeaponSocketType::SkeletalMesh:
		SkeletalMeshComponent = CastChecked<USkeletalMeshComponent>(MeshComponent);
		BaseSocketTransform = SkeletalMeshSocket->GetSocketTransform(SkeletalMeshComponent);
		break;

	default:
		checkNoEntry();
	}

}

const FRotator& FAttachedWeaponSocket::GetLaunchRotator() const
{
	return LaunchRotator;
}

const FVector& FAttachedWeaponSocket::GetLaunchLocation() const
{
	return LaunchLocation;
}

const FTransform& FAttachedWeaponSocket::GetBaseSocketTransform() const
{
	return BaseSocketTransform;
}

FAttachedWeaponSocket::FAttachedWeaponSocket()
{
}

FAttachedWeaponSocket::FAttachedWeaponSocket(EWeaponSocketAttachMode const InAttachMode, const FWeaponSocketConfig& InSocketConfig, const UStaticMeshSocket* const InSocket, UMeshComponent* const InMeshComponent)
: AttachMode {InAttachMode}
, SocketConfig {InSocketConfig}
, SocketType {EWeaponSocketType::StaticMesh}
, StaticMeshSocket {InSocket}
, MeshComponent {InMeshComponent}
{
	checkf(InSocket, TEXT("Passed socket must be valid NON-null pointer"));
	checkf(InMeshComponent, TEXT("Passed mesh component must be valid NON-null pointer"));
}

FAttachedWeaponSocket::FAttachedWeaponSocket(EWeaponSocketAttachMode const InAttachMode, const FWeaponSocketConfig& InSocketConfig, const USkeletalMeshSocket* const InSocket, UMeshComponent* const InMeshComponent)
: AttachMode {InAttachMode}
, SocketConfig {InSocketConfig}
, SocketType {EWeaponSocketType::SkeletalMesh}
, SkeletalMeshSocket {InSocket}
, MeshComponent {InMeshComponent}
{
	checkf(InSocket, TEXT("Passed socket must be valid NON-null pointer"));
	checkf(InMeshComponent, TEXT("Passed mesh component must be valid NON-null pointer"));
}

FQuickWeaponState::FQuickWeaponState()
{
}

FQuickWeaponState::FQuickWeaponState(FName const InWeaponName, const FQuickWeaponConfig& InConfig)
: WeaponName{InWeaponName}
, Config {InConfig}
{
}
