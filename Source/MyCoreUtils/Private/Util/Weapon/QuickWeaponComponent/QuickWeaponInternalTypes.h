#pragma once

#include "QuickWeaponTypes.h"
#include "QuickWeaponInternalTypes.generated.h"

USTRUCT(BlueprintType, Category = Weapon)
struct FQuickWeaponState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName WeaponName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FQuickWeaponConfig Config;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LastShootTime = 0.0F;

	/**
	* Default ctor: Creates uninitialized weapon state
	*/
	FQuickWeaponState();

	/**
	* Default ctor: Creates uninitialized weapon state
	*/
	FQuickWeaponState(FName InWeaponName, const FQuickWeaponConfig& InConfig);
};

/**
* Weapon socket info dependent on the attached actor
* (should be updated when the mesh or actor is changed!)
*/
USTRUCT(BlueprintType, Category = Weapon)
struct FAttachedWeaponSocket
{
	GENERATED_BODY()

	/**
	* Default Ctor: Creates UNINITIALIZED socket;
	*/
	FAttachedWeaponSocket();

	/**
	* Creates static mesh socket;
	*/
	FAttachedWeaponSocket(const EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const UStaticMeshSocket* InSocket, UMeshComponent* InMeshComponent);

	/**
	* Creates skeletal mesh socket;
	*/
	FAttachedWeaponSocket(const EWeaponSocketAttachMode InAttachMode, const FWeaponSocketConfig& InSocketConfig, const USkeletalMeshSocket* InSocket, UMeshComponent* InMeshComponent);

	FName GetWeaponName() const { return WeaponName; }
	EWeaponSocketAttachMode GetAttachMode() const { return AttachMode; }
	const FWeaponSocketConfig& GetSocketConfig() const { return SocketConfig; }
	EWeaponSocketType GetSocketType() const { return SocketType; }
	UMeshComponent* GetMeshComponent() const { return MeshComponent; }
	const UStaticMeshSocket* GetStaticMeshSocket() const { return StaticMeshSocket; }
	const USkeletalMeshSocket* GetSkeletalMeshSocket() const { return SkeletalMeshSocket; }

	/**
	* Final rotation of the socket transform, affected by offset and rotation.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FRotator& GetLaunchRotator() const;

	/**
	* Final location of the socket transform, affected by offset and rotation.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FVector& GetLaunchLocation() const;

	/**
	* Base transform of the socket.
	* In World Space.
	* Must be updated from socket!
	*
	* @see: UpdateFromSocket
	*/
	const FTransform& GetBaseSocketTransform() const;

	/**
	* This function to be called each time before calling GetLaunchRotator()/GetLaunchLocation()/GetBaseSocketTransform()
	*/
	void UpdateFromSocket();

private:
	void UpdateBaseSocketTransform();

	UPROPERTY()
	FName WeaponName;

	/** AttachMode*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(AllowPrivateAccess=true))
	EWeaponSocketAttachMode AttachMode = EWeaponSocketAttachMode::Manual;
	
	UPROPERTY()
	FWeaponSocketConfig SocketConfig;

	UPROPERTY()
	EWeaponSocketType SocketType = EWeaponSocketType::None;

	UPROPERTY()
	mutable FVector LaunchLocation = FVector::ZeroVector;

	UPROPERTY()
	mutable FRotator LaunchRotator = FRotator::ZeroRotator;

	UPROPERTY()
	mutable FTransform BaseSocketTransform;

	/** The static mesh socket we are attached to*/
	UPROPERTY()
	const UStaticMeshSocket* StaticMeshSocket = nullptr;

	UPROPERTY()
	const USkeletalMeshSocket* SkeletalMeshSocket = nullptr;

	UPROPERTY()
	UMeshComponent* MeshComponent = nullptr;
};
