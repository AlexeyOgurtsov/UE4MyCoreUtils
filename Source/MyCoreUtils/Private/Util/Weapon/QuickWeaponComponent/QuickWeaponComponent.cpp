#include "QuickWeaponComponent.h"
#include "QuickWeaponTypesLib.h"
#include "Util/Weapon/MyProjectileBase.h"
#include "Util/Core/LogUtilLib.h"

#include "Engine/World.h"

#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "Math/Transform.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"

#include "Misc/Optional.h"

namespace QuickWeaponComponentPriv
{
	TOptional<FAttachedWeaponSocket> CreateAttachedSocketByName(EWeaponSocketAttachMode InAttachMode, UStaticMeshComponent* Mesh, const FWeaponSocketConfig& InConfig);
	TOptional<FAttachedWeaponSocket> CreateAttachedSkeletalSocketByName(EWeaponSocketAttachMode InAttachMode, USkeletalMeshComponent* Mesh, const FWeaponSocketConfig& InConfig);
	FQuickWeaponState CreateWeaponState(UObject* WorldContextObject, FName InName, const FQuickWeaponConfig& InConfig);

	TOptional<FAttachedWeaponSocket> CreateAttachedSocketByName(EWeaponSocketAttachMode InAttachMode, UStaticMeshComponent* Mesh, const FWeaponSocketConfig& InConfig)
	{
		checkf(Mesh, TEXT("Mesh must be valid"));
		const UStaticMeshSocket* Socket = Mesh->GetSocketByName(InConfig.SocketName);
		if(nullptr == Socket) 
		{
			M_LOG_ERROR(TEXT("Socket with name \"%s\" is not found of the given mesh component (%s)"), *InConfig.SocketName.ToString(), *ULogUtilLib::GetNameAndClassSafe(Mesh));
			return TOptional<FAttachedWeaponSocket>();
		}
		FAttachedWeaponSocket AttachedSocket{InAttachMode, InConfig, Socket, Mesh};
		AttachedSocket.UpdateFromSocket();
		return AttachedSocket;
	}

	TOptional<FAttachedWeaponSocket> CreateAttachedSkeletalSocketByName(EWeaponSocketAttachMode InAttachMode, USkeletalMeshComponent* Mesh, const FWeaponSocketConfig& InConfig)
	{
		checkf(Mesh, TEXT("Mesh must be valid"));
		const USkeletalMeshSocket* Socket = Mesh->GetSocketByName(InConfig.SocketName);
		if(nullptr == Socket) 
		{
			M_LOG_ERROR(TEXT("Socket with name \"%s\" is not found of the given mesh component (%s)"), *InConfig.SocketName.ToString(), *ULogUtilLib::GetNameAndClassSafe(Mesh));
			return TOptional<FAttachedWeaponSocket>();
		}
		FAttachedWeaponSocket AttachedSocket{InAttachMode, InConfig, Socket, Mesh};
		AttachedSocket.UpdateFromSocket();
		return AttachedSocket;
	}

	FQuickWeaponState CreateWeaponState(UObject* WorldContextObject, FName InName, const FQuickWeaponConfig& InConfig)
	{
		return FQuickWeaponState(InName, InConfig);
	}
} // QuickWeaponComponentPriv

using namespace QuickWeaponComponentPriv;

UQuickWeaponComponent::UQuickWeaponComponent()
{
}

void UQuickWeaponComponent::PostInitProperties()
{
	Super::PostInitProperties();
	UpdateFromWeaponConfig();
}

void UQuickWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UQuickWeaponComponent::UpdateFromWeaponConfig()
{
	Weapons.Reset();
	for(const TPair<FName, FQuickWeaponConfig>& NameConfig : Config.Weapons)
	{
		Weapons.Add(NameConfig.Key, CreateWeaponState(this, NameConfig.Key, NameConfig.Value));
	}
}

void UQuickWeaponComponent::ReAttachToSockets()
{
	UpdateFromWeaponConfig();

	check(GetOwner());
	UStaticMeshComponent* FirstStaticMesh = GetOwner()->FindComponentByClass<UStaticMeshComponent>();
	USkeletalMeshComponent* FirstSkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();

	// Remove old sockets that were added automatically the last time!
	for(TMap<FName, FAttachedWeaponSocket>::TIterator SockIt = WeaponSockets.CreateIterator(); SockIt; ++SockIt)
	{
		if(SockIt->Value.GetAttachMode() == EWeaponSocketAttachMode::Automatic)
		{
			SockIt.RemoveCurrent();
		}
	}

	for(const FWeaponComponentSocketRef& SocketRef : SocketsToAttach)
	{
		UObject* SubobjectWithComponentName = nullptr;
		M_LOG(TEXT("Processing Socket-To-Attach: SocketName=\"%s\" ComponentName\"%s\""), *SocketRef.SocketName.ToString(), *SocketRef.ComponentName.ToString());
		if(SocketRef.IsBindedToComponent())
		{
			M_LOG(TEXT("Socket-To-Attach is binded to component with name \"%s\""), *SocketRef.ComponentName.ToString());
			SubobjectWithComponentName = GetOwner()->GetDefaultSubobjectByName(SocketRef.ComponentName);
			if(SubobjectWithComponentName == nullptr)
			{
				M_LOG_ERROR(TEXT("Component with name \"%s\" is not found"), *SocketRef.ComponentName.ToString());
			}
			else
			{
				checkf(SubobjectWithComponentName, TEXT("Subobject with component name is NOT nullptr (we are on the corresponding if branch)"));
				AttachSocketToComponentImpl(EWeaponSocketAttachMode::Automatic, SocketRef.ConfigRef.SocketName, Cast<UActorComponent>(SubobjectWithComponentName));
			}
		}
		else
		{
			M_LOG(TEXT("Socket-To-Attach is NOT binded to component"));
			UMeshComponent* FirstMeshComponent = (FirstStaticMesh != nullptr) ? (Cast<UMeshComponent>(FirstStaticMesh)) : (Cast<UMeshComponent>(FirstSkeletalMesh));
			if(FirstMeshComponent == nullptr)
			{
				M_LOG_ERROR(TEXT("Unable to attach socket by reference NON-binded to component: no socket-holding component found on the owning actor"));
			}
			else
			{
				AttachSocketToComponentImpl(EWeaponSocketAttachMode::Automatic, SocketRef.ConfigRef.SocketName, FirstMeshComponent);
			}
		}
	}
}

void UQuickWeaponComponent::AttachSocketToComponent(FName InWeaponSocketName, UActorComponent* Component)
{
	AttachSocketToComponentImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Component);
}

FAttachedWeaponSocket* UQuickWeaponComponent::AttachSocketToComponentImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UActorComponent* Component)
{
	M_LOGFUNC();
	M_LOG(TEXT("WeaponSocketName: \"%s\""), *InWeaponSocketName.ToString());
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Component"), Component);
	checkf(Component, TEXT("Passed component must be valid NON-null pointer"));
	if(Component->IsA(UStaticMeshComponent::StaticClass()))
	{
		return AttachSocketToStaticMeshImpl(InAttachMode, InWeaponSocketName, CastChecked<UStaticMeshComponent>(Component));
	}
	else if(Component->IsA(USkeletalMeshComponent::StaticClass()))
	{
		return AttachSocketToSkeletalMeshImpl(InAttachMode, InWeaponSocketName, CastChecked<USkeletalMeshComponent>(Component));
	}
	else
	{
		M_LOG_ERROR(TEXT("Component with name \"%s\" has unsupported class \"%s\""), *Component->GetName(), *Component->GetClass()->GetName());
		return nullptr;
	}
}

bool UQuickWeaponComponent::FireByName_Implementation(FName const InWeaponName)
{
	M_LOGFUNC_MSG(TEXT("WeaponName = %s"), *InWeaponName.ToString());

	FAttachedWeaponSocket* const AttachedSocket = GetAttachedWeaponSocketByWeaponName(InWeaponName);
	if(AttachedSocket == nullptr)
	{
		return false;
	}

	FQuickWeaponState* const Weapon = GetWeaponByName(InWeaponName);
	if(Weapon == nullptr)
	{
		return false;
	}

	if(CanFireWeapon(*Weapon))
	{
		AttachedSocket->UpdateFromSocket();
		FireWeaponFromSocket(*Weapon, *AttachedSocket);
		Weapon->LastShootTime = GetWorld()->GetTimeSeconds();
		return true;
	}
	else
	{
		return false;
	}
}

bool UQuickWeaponComponent::FireByIndex_Implementation(int32 const InWeaponIndex)
{
	M_LOGFUNC_MSG(TEXT("Fire: WeaponIndex = %d"), InWeaponIndex);
	if(InWeaponIndex >= Config.UsedWeaponNames.Num() || InWeaponIndex < 0)
	{
		M_LOG_ERROR(TEXT("Weapon index %d is out of range (Num used weapons=%d)"), InWeaponIndex, Config.UsedWeaponNames.Num());
		return false;
	}

	FName const WeaponName = Config.UsedWeaponNames[InWeaponIndex];
	bool const bFired = FireByName_Implementation(WeaponName);
	return bFired;
}

FAttachedWeaponSocket* UQuickWeaponComponent::GetAttachedWeaponSocketByWeaponName(FName const InWeaponName)
{
	TOptional<FName> const SocketName = GetSocketNameByWeaponName(InWeaponName);
	if( ! SocketName.IsSet() )
	{
		return nullptr;
	}

	FAttachedWeaponSocket* AttachedSocket = WeaponSockets.Find(SocketName.GetValue());
	if(AttachedSocket == nullptr)
	{
		M_LOG_ERROR(TEXT("Attached socket with name \"%s\" must be registered"), *SocketName.GetValue().ToString());
		return nullptr;
	}
	return AttachedSocket;
}

TOptional<FName> UQuickWeaponComponent::GetSocketNameByWeaponName(FName const InWeaponName) const
{
	FName const SocketName = Config.WeaponSocketNames.FindRef(InWeaponName);
	if( SocketName.IsNone() )
	{
		M_LOG_ERROR(TEXT("Socket for weapon named \"%s\" is NOT found"), *InWeaponName.ToString());
		return TOptional<FName>();
	}
	return SocketName;
}

FQuickWeaponState* UQuickWeaponComponent::GetWeaponByName(FName const InWeaponName)
{
	FQuickWeaponState* const Weapon = Weapons.Find(InWeaponName);
	if(Weapon == nullptr)
	{
		M_LOG_ERROR(TEXT("Weapon with name \"%s\" is not registered"), *InWeaponName.ToString());
		return nullptr;
	}
	return Weapon;
}

bool UQuickWeaponComponent::CanFireWeapon(const FQuickWeaponState& InWeapon) const
{
	float const CurrTime = GetWorld()->GetTimeSeconds();
	float const NextShootTime = InWeapon.LastShootTime + InWeapon.Config.MinFireInterval;
	if(CurrTime < NextShootTime)
	{
		M_LOG_ERROR(TEXT("Unable to fire"));
		M_LOG_ERROR(TEXT("(Next allowed shoot time: %f); CurrTime=%f, MinFireInterval=%f"), NextShootTime, CurrTime, InWeapon.Config.MinFireInterval);
		return false;
	}
	return true;
}

bool UQuickWeaponComponent::FireWeaponFromSocket(const FQuickWeaponState& InWeapon, const FAttachedWeaponSocket& InSocket)
{
	M_LOG
	(
	 	TEXT("Firing weapon \"%s\" from socket named \"%s\" on mesh \"%s\""),
		*InWeapon.WeaponName.ToString(),
	       	*InSocket.GetSocketConfig().SocketName.ToString(), 
		*ULogUtilLib::GetNameAndClassSafe(InSocket.GetMeshComponent())
	);
	if(InWeapon.Config.ProjectileClass == nullptr)
	{
		M_LOG_ERROR(TEXT("Unable to fire weapon from socket: ProjectileClass is nullptr"));
		return false;
	}

	M_LOG(TEXT("ProjectileClass: \"%s\" "), *InWeapon.Config.ProjectileClass->GetName());

	FActorSpawnParameters SpawnParams;
	FTransform ProjectileTransform {InSocket.GetLaunchRotator(), InSocket.GetLaunchLocation()};
	ULogUtilLib::LogTransformC(TEXT("Transform: "), ProjectileTransform);

	AMyProjectileBase* const Projectile = Cast<AMyProjectileBase>(GetWorld()->SpawnActor
	(
		InWeapon.Config.ProjectileClass, 
		&ProjectileTransform,
		SpawnParams
	)); 

	if( ! IsValid(Projectile) )
	{
		M_LOG_ERROR(TEXT("IsValid returned false for the spawned projectile!"));
		return false;
	}

	Projectile->Launch();
	return true;
}

void UQuickWeaponComponent::DetachFromMesh()
{
	WeaponSockets.Reset();
}

void UQuickWeaponComponent::AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh)
{
	AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Mesh);
}

void UQuickWeaponComponent::AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode::Manual, InWeaponSocketName, Mesh);
}

FAttachedWeaponSocket* UQuickWeaponComponent::AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UStaticMeshComponent* Mesh)
{
	M_LOGFUNC();
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	FWeaponSocketConfig* const SocketConfig = GetSocketByName(InWeaponSocketName);
	if(SocketConfig == nullptr)
	{
		return nullptr;
	}

	TOptional<FAttachedWeaponSocket> const AttachedSocket = CreateAttachedSocketByName(InAttachMode, Mesh, *SocketConfig);
	if( ! AttachedSocket.IsSet() )
	{
		return nullptr;
	}

	return &WeaponSockets.Add(InWeaponSocketName, AttachedSocket.GetValue());
}

FAttachedWeaponSocket* UQuickWeaponComponent::AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, USkeletalMeshComponent* Mesh)
{
	M_LOGFUNC();
	checkf(Mesh, TEXT("Passed Mesh pointer must be valid"));
	FWeaponSocketConfig* const SocketConfig = GetSocketByName(InWeaponSocketName);
	if(SocketConfig == nullptr)
	{
		return nullptr;
	}

	TOptional<FAttachedWeaponSocket> const AttachedSocket = CreateAttachedSkeletalSocketByName(InAttachMode, Mesh, *SocketConfig);
	if( ! AttachedSocket.IsSet() )
	{
		return nullptr;
	}

	return &WeaponSockets.Add(InWeaponSocketName, AttachedSocket.GetValue());
}

FWeaponSocketConfig* UQuickWeaponComponent::GetSocketByName(FName InSocketName)
{
	FWeaponSocketConfig* const SocketConfig = Config.Sockets.Find(InSocketName);
	if(SocketConfig == nullptr)
	{
		M_LOG(TEXT("Config for socket with name \"%s\" is NOT found"), *InSocketName.ToString());
		return nullptr;
	}
	return SocketConfig;
}
