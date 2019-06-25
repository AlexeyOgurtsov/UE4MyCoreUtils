#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "PropertyLib.generated.h"

UCLASS()
class UPropertyLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Returns value of container UObject if it's a UObject-containing property (script interface property, object property base).
	* Otherwise returns nullptr.
	*/
	static const UObject* GetPropertyValueAsObject(const UProperty* InProperty, const void* InValue);

	/**
	* @see: GetPropertyValueAsObject(..., const void* InValue)
	*/
	static UObject* GetPropertyValueAsObject(const UProperty* InProperty, void* InValue);
};