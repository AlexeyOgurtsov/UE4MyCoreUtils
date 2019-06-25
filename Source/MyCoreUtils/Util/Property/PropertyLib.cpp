#include "PropertyLib.h"

const UObject* UPropertyLib::GetPropertyValueAsObject(const UProperty* InProperty, const void* InValue)
{
	if(const UObjectPropertyBase* PropAsObject = Cast<const UObjectPropertyBase>(InProperty))
	{
		return PropAsObject->GetObjectPropertyValue(InValue);
	}
	else if(const UInterfaceProperty* PropAsInterface = Cast<const UInterfaceProperty>(InProperty))
	{
		return UInterfaceProperty::GetPropertyValue(InValue).GetObject();
	}
	return nullptr;
}

UObject* UPropertyLib::GetPropertyValueAsObject(const UProperty* InProperty, void* InValue)
{
	return const_cast<UObject*>(GetPropertyValueAsObject(InProperty, const_cast<const void*>(InValue)));
}
