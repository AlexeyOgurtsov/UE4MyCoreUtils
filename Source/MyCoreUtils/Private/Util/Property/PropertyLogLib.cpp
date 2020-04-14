#include "PropertyLogLib.h"
#include "UObject/TextProperty.h"
#include "Util/Core/SystemUtils.h"

FString UPropertyLogLib::GetPropertyChangeTypeString(EPropertyChangeType::Type InChangeType)
{
	#define M_CASE_PREFIX() EPropertyChangeType::
	M_SWITCH_BEGIN(InChangeType)
		M_CASE_ENUM_PREFIX_STRING(Unspecified);
		M_CASE_ENUM_PREFIX_STRING(ArrayAdd);
		M_CASE_ENUM_PREFIX_STRING(ArrayRemove);
		M_CASE_ENUM_PREFIX_STRING(ArrayClear);
		M_CASE_ENUM_PREFIX_STRING(ValueSet);
		M_CASE_ENUM_PREFIX_STRING(Duplicate);
		M_CASE_ENUM_PREFIX_STRING(Interactive);
		M_CASE_ENUM_PREFIX_STRING(Redirected);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}

void UPropertyLogLib::LogPropertyChangedEvent(const FPropertyChangedEvent& InEvent)
{
	M_LOGFUNC();

	ULogUtilLib::LogStringC(TEXT("ChangeType"), GetPropertyChangeTypeString(InEvent.ChangeType));
	ULogUtilLib::LogStringC(TEXT("MemberProperty"), *GetFieldString(InEvent.MemberProperty));
	ULogUtilLib::LogInt32C(TEXT("ObjectIteratorIndex"), InEvent.ObjectIteratorIndex);
	ULogUtilLib::LogStringC(TEXT("Property"), *GetFieldString(InEvent.Property));
}

FString UPropertyLogLib::GetFieldString(const FField* const InField, EFieldStringFlags const InFlags)
{
	FString Result;

	if((InFlags & EFieldStringFlags::ExcludeOwner) == EFieldStringFlags::None)
	{
		Result.Append(TEXT("OwnerStruct={"));		
		Result.Append(ULogUtilLib::GetNameAndClassSafe(InField->GetOwnerStruct()));	
		Result.Append(TEXT("}; "));		
	}
	
	return Result;
}

FString UPropertyLogLib::GetFieldString(const UField* const InField, EFieldStringFlags const InFlags)
{
	FString Result;

	if ((InFlags & EFieldStringFlags::ExcludeOwner) == EFieldStringFlags::None)
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
	for(FPropertyValueIterator Itr { FProperty::StaticClass(), InStruct, InStructValue }; Itr; ++Itr)
	{
		LogPropertyValue(Itr.Key(), Itr.Value());
	}
}

void UPropertyLogLib::LogPropertyValue(const FProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	M_LOG(TEXT("{%s} value is {%s}"), *GetFieldString(InProperty), *GetPropertyValueString(InProperty, InValue, InFlags));
}

FString UPropertyLogLib::GetPropertyValueString(const FProperty* const InProperty, const void* InValue, EPropertyValueStringFlags const InFlags)
{
	/*
	if(const FNumericProperty* PropAsNumeric = Cast<const FNumericProperty>(InProperty))
	{
		return PropAsNumeric->GetNumericPropertyValueToString(InValue);
	}
	else if(const FBoolProperty* PropAsBool = Cast<const FBoolProperty>(InProperty))
	{
		return PropAsBool->GetPropertyValue(&InValue) ? FString(TEXT("TRUE")) : FString(TEXT("false"));
	}
	else if(const FObjectPropertyBase* PropAsObj = Cast<const FObjectPropertyBase>(InProperty))
	{
		return ULogUtilLib::GetNameAndClassSafe(PropAsObj->GetObjectPropertyValue(InValue));
	}
	else if(const FClassProperty* PropAsClass = Cast<const FClassProperty>(InProperty))
	{
		return PropAsClass->MetaClass ? PropAsClass->MetaClass->GetName() : FString(TEXT("nullptr"));
	}
	else if(const FInterfaceProperty* PropAsInterface = Cast<const FInterfaceProperty>(InProperty))
	{
		return ULogUtilLib::GetNameAndClassSafe(FInterfaceProperty::GetPropertyValue(InValue).GetObject());
	}
	else if(const FNameProperty* PropAsName = Cast<const FNameProperty>(InProperty))
	{
		return FNameProperty::GetPropertyValue(InValue).ToString();
	}
	else if(const FStrProperty* PropAsString = Cast<const FStrProperty>(InProperty))
	{
		return FStrProperty::GetPropertyValue(InValue);
	}
	else if(const FArrayProperty* PropAsArray = Cast<const FArrayProperty>(InProperty))
	{
		return GetArrayPropertyValueString(PropAsArray, InValue, InFlags);
	}
	else if(const FMapProperty* PropAsMap = Cast<const FMapProperty>(InProperty))
	{
		return GetMapPropertyValueString(PropAsMap, InValue, InFlags);
	}
	else if(const FSetProperty* PropAsSet = Cast<const FSetProperty>(InProperty))
	{
		return GetSetPropertyValueString(PropAsSet, InValue, InFlags);
	}
	else if(const FStructProperty* PropAsStruct = Cast<FStructProperty>(InProperty))
	{
		return FString(TEXT("{STRUCT}"));
	}
	else if(const FDelegateProperty* PropAsDelegate = Cast<const FDelegateProperty>(InProperty))
	{
		return PropAsDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const FMulticastDelegateProperty* PropAsMultiDelegate = Cast<const FMulticastDelegateProperty>(InProperty))
	{
		return PropAsMultiDelegate->SignatureFunction ? FString(TEXT("SET")) : FString(TEXT("nullptr"));
	}
	else if(const FTextProperty* PropAsText = Cast<const FTextProperty>(InProperty))
	{
		return FTextProperty::GetPropertyValue(InValue).ToString();
	}
	else
	{
		return FString(TEXT("{UNKNOWN_PROP_TYPE}"));
	}
	*/
	return FString(TEXT("NotYetImpl_until4.25"));
}

FString UPropertyLogLib::GetArrayPropertyValueString(const FArrayProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptArray* const Arr = FArrayProperty::GetPropertyValuePtr(InValue);
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

FString UPropertyLogLib::GetSetPropertyValueString(const FSetProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptSet* const Set = FSetProperty::GetPropertyValuePtr(InValue);
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

FString UPropertyLogLib::GetMapPropertyValueString(const FMapProperty* const InProperty, const void* const InValue, EPropertyValueStringFlags const InFlags)
{
	check(InProperty);
	check(InValue);
	
	FString S;
	const FScriptMap* const Map = FMapProperty::GetPropertyValuePtr(InValue);
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

FString UPropertyLogLib::GetFieldStringSafe(const FField* const InField, EFieldStringFlags const InFlags)
{
	if (InField == nullptr)
	{
		return FString(TEXT("{nullptr}"));
	}
	return GetFieldString(InField, InFlags);
}

FString UPropertyLogLib::GetFieldStringSafe(const UField* const InField, EFieldStringFlags const InFlags)
{
	if(InField == nullptr)
	{
		return FString(TEXT("{nullptr}"));
	}
	return GetFieldString(InField, InFlags);
}
