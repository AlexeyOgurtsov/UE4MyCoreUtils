#include "PropertyLogLib.h"

FString UPropertyLogLib::GetFieldString(const UField* const InField, EFieldStringFlags const InFlags)
{
	FString Result;

	if((InFlags & EFieldStringFlags::ExcludeOwner) == EFieldStringFlags::None)
	{
		Result.Append(TEXT("OwnerStruct={"));		
		Result.Append(ULogUtilLib::GetNameAndClassSafe(InField->GetOwnerStruct()));	
		Result.Append(TEXT("}; "));		
	}

	Result.Append(ULogUtilLib::GetNameAndClassSafe(InField));
	
	return Result;
}

void UPropertyLogLib::LogStructPropertyValues(const UStruct* const InStruct, const void* const InStructValue)
{
	for(FPropertyValueIterator Itr { UProperty::StaticClass(), InStruct, InStructValue }; Itr; ++Itr)
	{
		LogPropertyValue(Itr.Key(), Itr.Value());
	}
}

void UPropertyLogLib::LogPropertyValue(const UProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	M_LOG(TEXT("{%s} value is {%s}"), *GetFieldString(InProperty), *GetPropertyValueString(InProperty, InValue, InFlags));
}

FString UPropertyLogLib::GetPropertyValueString(const UProperty* const InProperty, const void* InValue, EPropertyValueStringFlags const InFlags)
{
	if(const UNumericProperty* PropAsNumeric = Cast<const UNumericProperty>(InProperty))
	{
		return PropAsNumeric->GetNumericPropertyValueToString(InValue);
	}
	else if(const UBoolProperty* PropAsBool = Cast<const UBoolProperty>(InProperty))
	{
		return PropAsBool->GetPropertyValue(&InValue) ? FString(TEXT("TRUE")) : FString(TEXT("false"));
	}
	else if(const UObjectPropertyBase* PropAsObj = Cast<const UObjectPropertyBase>(InProperty))
	{
		return ULogUtilLib::GetNameAndClassSafe(PropAsObj->GetObjectPropertyValue(InValue));
	}
	else if(const UClassProperty* PropAsClass = Cast<const UClassProperty>(InProperty))
	{
		return PropAsClass->MetaClass ? PropAsClass->MetaClass->GetName() : FString(TEXT("nullptr"));
	}
	else if(const UInterfaceProperty* PropAsInterface = Cast<const UInterfaceProperty>(InProperty))
	{
		return ULogUtilLib::GetNameAndClassSafe(UInterfaceProperty::GetPropertyValue(InValue).GetObject());
	}
	else if(const UNameProperty* PropAsName = Cast<const UNameProperty>(InProperty))
	{
		return UNameProperty::GetPropertyValue(InValue).ToString();
	}
	else if(const UStrProperty* PropAsString = Cast<const UStrProperty>(InProperty))
	{
		return UStrProperty::GetPropertyValue(InValue);
	}
	else if(const UArrayProperty* PropAsArray = Cast<const UArrayProperty>(InProperty))
	{
		return GetArrayPropertyValueString(PropAsArray, InValue, InFlags);
	}
	else if(const UMapProperty* PropAsMap = Cast<const UMapProperty>(InProperty))
	{
		return GetMapPropertyValueString(PropAsMap, InValue, InFlags);
	}
	else if(const USetProperty* PropAsSet = Cast<const USetProperty>(InProperty))
	{
		return GetSetPropertyValueString(PropAsSet, InValue, InFlags);
	}
	else if(const UStructProperty* PropAsStruct = Cast<UStructProperty>(InProperty))
	{
		return FString(TEXT("{STRUCT}"));
	}
	else if(const UDelegateProperty* PropAsDelegate = Cast<const UDelegateProperty>(InProperty))
	{
		return PropAsDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const UMulticastDelegateProperty* PropAsMultiDelegate = Cast<const UMulticastDelegateProperty>(InProperty))
	{
		return PropAsMultiDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const UTextProperty* PropAsText = Cast<const UTextProperty>(InProperty))
	{
		return UTextProperty::GetPropertyValue(InValue).ToString();
	}
	else
	{
		return FString(TEXT("{UNKNOWN_PROP_TYPE}"));
	}
}

FString UPropertyLogLib::GetArrayPropertyValueString(const UArrayProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptArray* const Arr = UArrayProperty::GetPropertyValuePtr(InValue);
	if(Arr)
	{
		S.Append(FString::Printf(TEXT("Count=%d"), Arr->Num()));
	}
	else
	{
		S.Append(FString{TEXT("{PropertyValuePtr is nullptr}")});
	}

	return S;
}

FString UPropertyLogLib::GetSetPropertyValueString(const USetProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptSet* const Set = USetProperty::GetPropertyValuePtr(InValue);
	if(Set)
	{
		S.Append(FString::Printf(TEXT("Count=%d"), Set->Num()));
	}
	else
	{
		S.Append(FString{TEXT("{PropertyValuePtr is nullptr}")});
	}

	return S;
}

FString UPropertyLogLib::GetMapPropertyValueString(const UMapProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptMap* const Map = UMapProperty::GetPropertyValuePtr(InValue);
	if(Map)
	{
		S.Append(FString::Printf(TEXT("Count=%d"), Map->Num()));
	}
	else
	{
		S.Append(FString{TEXT("{PropertyValuePtr is nullptr}")});
	}

	return S;
}

FString UPropertyLogLib::GetFieldStringSafe(const UField* const InField, EFieldStringFlags const InFlags)
{
	if(InField == nullptr)
	{
		return FString(TEXT("{nullptr}"));
	}
	return GetFieldString(InField, InFlags);
}