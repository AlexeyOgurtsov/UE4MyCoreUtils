#pragma once

/**
* All weapon inventory components are to be inherited from this class.
*/

#include "Components/ActorComponent.h"
#include "I/IWeaponInventory.h"
#include "WeaponComponent.generated.h"

UCLASS(Category=Weapon, ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent))
class UWeaponComponent : 
	public UActorComponent
,	public IWeaponInventory
{
	GENERATED_BODY()
	
public:
	UWeaponComponent();

protected:
private:
};

