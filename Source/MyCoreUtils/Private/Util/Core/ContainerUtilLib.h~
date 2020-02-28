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
	* @param: TRange: any range of pointers (const or mutable) to UObject-derived objects.
	*
	* @returns: true, if the given object set contains object that is subclassed from the given class.
	*/
	template<class RangeT>
	static bool ContainsChildOf(const RangeT& InRange, const UClass* InClass)
	{
		return FindChildOf(InRange, InClass) != nullptr;
	}

	/**
	* @returns: pointer to pointer to ElementType of the range (nullptr if not found)
	*/
	template<class RangeT>
	static typename const RangeT::ElementType* FindChildOf(const RangeT& InRange, const UClass* InClass)
	{
		return FindChildOfImpl<const RangeT::ElementType, const RangeT>(InRange, InClass, TEXT(__FUNCTION__));
	}

	template<class RangeT>
	static typename RangeT::ElementType* FindChildOf(RangeT& InRange, const UClass* InClass)
	{
		return FindChildOfImpl<RangeT::ElementType, RangeT>(InRange, InClass, TEXT(__FUNCTION__));
	}


	/**
	* @param RangeT: range of const UClass* or UClass*
	*
	* @returns: true if subclass of the given class is found in the given set.
	*/
	template<class RangeT>
	static bool ContainsSubclassOf(const RangeT& InRange, const UClass* InClass)
	{
		return FindSubclassOf(InRange, InClass) != nullptr;
	}

	UFUNCTION(BlueprintCallable, Category = ContainerUtil, Meta=(DisplayName="SetContainsSubclassOf"))
	static bool K2SetContainsSubclassOf(const TSet<UClass*> InSet, const UClass* InClass)
	{
		return ContainsSubclassOf(InSet, InClass);
	}

	UFUNCTION(BlueprintCallable, Category = ContainerUtil, Meta=(DisplayName="ArrayContainsSubclassOf"))
	static bool K2ArrayContainsSubclassOf(const TArray<UClass*> InArray, const UClass* InClass)
	{	
		return ContainsSubclassOf(InArray, InClass);
	}

	/**
	* @returns: pointer to pointer to ElementType of the range (nullptr if not found)
	*/
	template<class RangeT>
	static typename const RangeT::ElementType* FindSubclassOf(const RangeT& InRange, const UClass* const InClass)
	{
		return FindSubclassOfImpl<const RangeT::ElementType, const RangeT>(InRange, InClass, TEXT(__FUNCTION__));
	}

	/**
	* @returns: pointer to pointer to ElementType of the range (nullptr if not found)
	*/
	template<class RangeT>
	static typename RangeT::ElementType* FindSubclassOf(RangeT& InRange, const UClass* const InClass)
	{
		return FindSubclassOfImpl<RangeT::ElementType, RangeT>(InRange, InClass, TEXT(__FUNCTION__));
	}

private:
	template<class ElementT, class RangeT>
	static typename ElementT* FindSubclassOfImpl(RangeT& InRange, const UClass* const InClass, const TCHAR* InFunctionName)
	{
		checkf(InClass, TEXT("when calling %s class to search must be valid pointer"), InFunctionName);
		for(ElementT& pCurrClass : InRange)
		{
			if(pCurrClass == nullptr)
			{
				continue;
			}

			if(pCurrClass->IsChildOf(InClass))
			{
				return &pCurrClass;
			}
			
		}
		return nullptr;
	}
	template<class ElementT, class RangeT>
	static typename ElementT* FindChildOfImpl(RangeT& InRange, const UClass* InClass, const TCHAR* InFunctionName)
	{
		checkf(InClass, TEXT("when calling %s class to search must be valid pointer"), InFunctionName);
		
		for(ElementT& pCurrObject : InRange)
		{
			if(pCurrObject == nullptr)
			{
				continue;
			}

			if(pCurrObject->GetClass()->IsChildOf(InClass))
			{
				return &pCurrObject;
			}
		}
		return nullptr;
	}
};
