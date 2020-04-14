#pragma once

#include "UObject/Interface.h"
#include "IWeaponInventory.generated.h"

UINTERFACE()
class UWeaponInventory : public UInterface
{
	GENERATED_BODY()

public:
};

class IWeaponInventory
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool FireByIndex(int32 InWeaponIndex);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool FireByName(FName InWeaponName);
};
