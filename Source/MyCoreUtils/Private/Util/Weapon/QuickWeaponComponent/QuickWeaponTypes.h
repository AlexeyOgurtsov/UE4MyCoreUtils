#pragma once

#include "Containers/Map.h"
#include "Templates/SubclassOf.h"
#include "QuickWeaponTypes.generated.h"

class AMyProjectileBase;

USTRUCT(BlueprintType, Category=Weapon)
struct FQuickWeaponConfig
{
	GENERATED_BODY()

	/** ProjectileClass*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AMyProjectileBase> ProjectileClass;

	/** MinFireInterval*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinFireInterval = 1.0F;
	
};

USTRUCT(BlueprintType, Category=Weapon)
struct FWeaponSocketConfig
{
	GENERATED_BODY()

	/**
	* Name of the socket on the mesh
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	/** SocketOffset*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector SocketOffset = FVector::ZeroVector;
	
	/** SocketRotation*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator SocketRotation = FRotator::ZeroRotator;
};

class UStaticMeshSocket;
class USkeletalMeshSocket;
class UMeshComponent;

/** ESocketType*/
UENUM(BlueprintType, Category=Misc)
enum class EWeaponSocketType : uint8
{
	None UMETA(DisplayName="None"),

	/** StaticMesh*/
	StaticMesh UMETA(DisplayName="StaticMesh")

	/** SkeletalMesh*/
	, SkeletalMesh UMETA(DisplayName="SkeletalMesh")
};

/** EWeaponSocketAttachMode*/
UENUM(BlueprintType, Category=Misc)
enum class EWeaponSocketAttachMode : uint8
{
	/** Manual*/
	Manual UMETA(DisplayName="Manual")

	/** Automatic*/
	, Automatic UMETA(DisplayName="Automatic")
};

USTRUCT(BlueprintType)
struct FWeaponComponentConfigRef
{
	GENERATED_BODY()

	/**
	* Name of the socket 
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	FWeaponComponentConfigRef() {}
	FWeaponComponentConfigRef(FName InSocketName)
	: SocketName(InSocketName) {}
};


USTRUCT(BlueprintType)
struct FWeaponComponentSocketRef
{
	GENERATED_BODY()
	
	/**
	* Links to config (which weapon and socket config should we use?)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeaponComponentConfigRef ConfigRef;

	/**
	* Name of the socket on the component
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName SocketName;

	/**
	* Name of the component (of None if linked with First component, not with particular component)
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ComponentName;

	bool IsBindedToComponent() const { return ! ComponentName.IsNone(); }

	/**
	* Default ctor: Constructs reference that is NOT binded to any socket
	*/
	FWeaponComponentSocketRef() {}

	FWeaponComponentSocketRef(const FWeaponComponentConfigRef& InConfigRef, FName InSocketName, FName InComponentName)
	: ConfigRef(InConfigRef)
	, SocketName(InSocketName)
	, ComponentName(InComponentName) {}

	/**
	* Constructs reference that is binded to the socket of the given name on the first component.
	*/
	FWeaponComponentSocketRef(const FWeaponComponentConfigRef& InConfigRef, FName InSocketName)
	: ConfigRef(InConfigRef)
	, SocketName(InSocketName) 
	, ComponentName(NAME_None) {}
};

/*
* Quick version of weapon inventory configuration
*/
USTRUCT(BlueprintType, Category=Weapon)
struct FQuickWeaponInventoryConfig
{
	GENERATED_BODY()
	
	/** Weapon sockets keyed by name*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FWeaponSocketConfig> Sockets;

	/** Weapons keyed by name*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FQuickWeaponConfig> Weapons;

	/** Maps weapon names to socket names */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FName, FName> WeaponSocketNames;

	/**
	* Mapping of weapons to indices
	*/
	TArray<FName> UsedWeaponNames;

	void RegisterSocket(FName InUniqueName, const FWeaponSocketConfig& InConfig);
	void RegisterWeapon(FName InUniqueName, const FQuickWeaponConfig& InConfig);
	void SetWeaponToSocketChecked(const FWeaponSocketConfig& InSocket, const FQuickWeaponConfig& InWeapon);
	void SetWeaponToSocketChecked(FName InSocketName, FName InWeaponName);
	const FQuickWeaponConfig& GetWeaponByIndex(int32 InIndex) const;
};
