#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "QuickWeaponTypes.h"
#include "QuickWeaponTypesLib.generated.h"

class UStaticMeshComponent;
class USkeletalMeshComponent;
class UQuickWeaponComponent;
class UMeshComponent;

const FName PRIMARY_WEAPON_NAME = "PrimaryWeapon";
const FName PRIMARY_WEAPON_SOCKET_NAME = "PrimaryWeaponSocket";

UCLASS()
class UQuickWeaponTypesLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static bool InitializePrimaryWeapon(UQuickWeaponComponent* WeaponComponent, FName InComponentName = NAME_None);

	/**
	* If NAME_None is used for the component name, then the first component will be used.
	*
	* WeaponName will be used as name both for socket and the weapon.
	*
	* @returns: true if socket was added, otherwise returns false.
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static bool AddSocketWithWeapon(UQuickWeaponComponent* WeaponComponent, FName InWeaponName, const FQuickWeaponConfig& InWeapon, const FWeaponSocketConfig& InSocket, FName InComponentName = NAME_None);

	/**
 	* Adds socket if the socket with the given name has not been added yet.
	* Performs logging.
	*
	* @returns: true if socket was added (or return false if socket with the given name already registered)
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static bool AddNewWeaponSocket(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, FName InSocketName, const FWeaponSocketConfig& InSocketConfig);

	/**
 	* Adds weapon if the weapon with the given name has not been added yet.
	* Performs logging.
	*
	* @returns: true if the weapon was added (or return false if weapon with the given name already registered)
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static bool AddNewWeapon(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, FName InWeaponName, const FQuickWeaponConfig& InWeaponConfig);

	/**
	* Binds socket to the given weapon if the weapon has not been bound to socket yet.
	*
	* @returns: true if the weapon was bound to socket now.
	*/
	UFUNCTION(BlueprintCallable, Category = Weapon)
	static bool SetSocketToWeapon(UPARAM(Ref) FQuickWeaponInventoryConfig& Config, FName InWeaponName, FName InSocketName);
};
