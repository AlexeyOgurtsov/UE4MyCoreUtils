#pragma once

#include "UObject/Interface.h"
#include "IWeaponInventoryHolder.generated.h"

class IWeaponInventory;

UINTERFACE()
class UWeaponInventoryHolder : public UInterface
{
	GENERATED_BODY()

public:
};

class IWeaponInventoryHolder
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	TScriptInterface<IWeaponInventory> GetWeapons() const;
};
