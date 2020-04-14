#pragma once

#include "Util/Weapon/WeaponComponent.h"
#include "QuickWeaponInternalTypes.h"
#include "QuickWeaponComponent.generated.h"


class UActorComponent;
class UStaticMeshComponent;
class USkeletalMeshComponent;

/**
* Usage scenario:
* 1. Fill Config : FQuickWeaponInventoryConfig (maybe declaratively)	
* 2. Fill SocketsToAttach with sockets (maybe declaratively)
* 	// Add socket on unknown component:
* 	Weapon->SocketsToAttach.Add(FWeaponComponentSocketRef{TEXT("FrontGun")});
* 	// Add socket on the given component:
* 	Weapon->SocketsToAttach.Add(FWeaponComponentSocketRef{MeshComp, TEXT("TopGun")});
* 3. Call ReAttachToSockets (typically inside the Actor's BeginPlay)
* 	Weapon->ReAttachToSockets();
*/
UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UQuickWeaponComponent : 
	public UWeaponComponent
{
	GENERATED_BODY()
	
public:
	UQuickWeaponComponent();

	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	
	// ~ Mesh attachment Begin
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void DetachFromMesh();

	/*
	* Attach socket to mesh component
	*
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToMesh(FName InWeaponSocketName, UStaticMeshComponent* Mesh);

	/*
	* Attach socket to mesh component
	*
	* @see AttachSocketToMesh
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToSkeletalMesh(FName InWeaponSocketName, USkeletalMeshComponent* Mesh);


	UFUNCTION(BlueprintCallable, Category = MeshAttachment)
	void AttachSocketToComponent(FName InWeaponSocketName, UActorComponent* Component);

	/**
	* This set of sockets is to be automatically attached on call to ReAttachToSockets.
	* So you can define them here declaratively.
	* @see: ReAttachToSockets
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	TArray<FWeaponComponentSocketRef> SocketsToAttach;

	/**
	* Configuration of the weapon inventory.
	*
	* @warning: UpdateFromWeaponConfig must be called after the weapon config is updated to affect changes!
	* (However, it should not be called if config is defined declaratively, 
	* because the config is automatically updated inside the PostInitProperties)
	*
	* @see UpdateFromWeaponConfig
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon)
	FQuickWeaponInventoryConfig Config;

	/**
	* Updates internal state of the weapon from the config
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void UpdateFromWeaponConfig();

	/**
	* Reattach to sockets:
	* Attaches sockets enlisted within the SocketsToAttach.
	* Automatically updates from weapon config.
	*
	* It does NOT clear sockets added manually!
	* 
	* WARNING! Must be called manually (typically inside the Actor's BeginPlay call)
	* (We could not call it inside this component's BeginPlay automatically
	* as the other components that are referenced inside the SocketsToAttach array
	* are not necessarily added yet)
	* @see SocketsToAttach
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void ReAttachToSockets();
	// ~ Mesh attachment End
	
	// ~ IWeaponInventory Begin
	virtual bool FireByIndex_Implementation(int32 InWeaponIndex) override;
	virtual bool FireByName_Implementation(FName InWeaponName) override;
	// ~ IWeaponInventory End

protected:
private:
	TOptional<FName> GetSocketNameByWeaponName(FName InWeaponName) const;
	FAttachedWeaponSocket* GetAttachedWeaponSocketByWeaponName(FName InSocketName);
	FQuickWeaponState* GetWeaponByName(FName InSocketName);
	FWeaponSocketConfig* GetSocketByName(FName InSocketName);

	bool FireWeaponFromSocket(const FQuickWeaponState& InWeapon, const FAttachedWeaponSocket& InSocket);
	bool CanFireWeapon(const FQuickWeaponState& InWeapon) const;

	FAttachedWeaponSocket* AttachSocketToSkeletalMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, USkeletalMeshComponent* Mesh);
	FAttachedWeaponSocket* AttachSocketToStaticMeshImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UStaticMeshComponent* Mesh);
	FAttachedWeaponSocket* AttachSocketToComponentImpl(EWeaponSocketAttachMode InAttachMode, FName InWeaponSocketName, UActorComponent* Component);

	UPROPERTY()
	TMap<FName, FAttachedWeaponSocket> WeaponSockets;

	UPROPERTY()
	TMap<FName, FQuickWeaponState> Weapons;
};

