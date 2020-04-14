#include "PropertyLib.h"

const UObject* UPropertyLib::GetPropertyValueAsObject(const FProperty* InProperty, const void* InValue)
{
	/*
	if(const FObjectPropertyBase* PropAsObject = Cast<const FObjectPropertyBase>(InProperty))
	{
		return PropAsObject->GetObjectPropertyValue(InValue);
	}
	else if(const FInterfaceProperty* PropAsInterface = Cast<const FInterfaceProperty>(InProperty))
	{
		return FInterfaceProperty::GetPropertyValue(InValue).GetObject();
	}
	*/
	return nullptr;
}

UObject* UPropertyLib::GetPropertyValueAsObject(const FProperty* InProperty, void* InValue)
{
	return const_cast<UObject*>(GetPropertyValueAsObject(InProperty, const_cast<const void*>(InValue)));
}
