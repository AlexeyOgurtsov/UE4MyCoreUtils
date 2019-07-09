#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util/Core/MyDebugMacros.h"
#include "ContainerUtilLib.generated.h"

UCLASS()
class UContainerUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* @param T: must be subclass of UObject.
	*
	* @returns: true, if the given object set contains object that is subclassed from the given class.
	*/
	template<class T>
	static bool ContainsChildOf(const TSet<T*>& InRange, const UClass* InClass);

	template<class T>
	static T** FindChildOf(const TSet<T*>& InRange, const UClass* InClass)
	{
		M_NOT_IMPL_RET(nullptr);
	}

	/**
	* @param: TRange: any range of pointers (const or mutable) to UObject-derived objects.
	*
	* @see: ContainsChildOf
	*/
	template<class TRange>
	static bool RangeContainsChildOf(const TRange& InRange, const UClass* InClass);

	/**
	* @returns: true if subclass of the given class is found in the given set.
	*/
	static bool ContainsSubclassOf(const TSet<const UClass*>& InSet, const UClass* InClass);
	static bool ContainsSubclassOf(const TSet<UClass*>& InSet, const UClass* InClass);

	static const UClass** FindSubclassOf(const TSet<const UClass*>& InSet, const UClass* InClass);
	static UClass** FindSubclassOf(const TSet<UClass*>& InSet, const UClass* InClass);

	/**
	* @param: InRange: range of UClass* or const UClass*
	*
	* @see ContainsSubclassOf
	*/
	template<class TRange>
	static bool RangeContainsSubclassOf(const TRange& InRange, const UClass* InClass);
};
