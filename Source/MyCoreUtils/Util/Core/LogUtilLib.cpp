#include "LogUtilLib.h"

DEFINE_LOG_CATEGORY(MyLog);

ULogUtilLib::ULogUtilLib()
{
}

FString ULogUtilLib::GetNameAndClass(const UObject* const InObject)
{
	checkf(InObject, TEXT("nullptr is invalid when using  %s, use Safe version instead"), __FUNCTION__);
	TArray<FStringFormatArg> FormatArgs;
	FormatArgs.Add(InObject->GetName());
	FormatArgs.Add(InObject->GetClass()->GetName());
	return FString::Format(TEXT("name=\"{0}\" class=\"{1}\""), FormatArgs);
}

FString ULogUtilLib::GetNameAndClassSafe(const UObject* const InObject)
{
	if(nullptr == InObject)
	{
		return FString(TEXT("nullptr"));
	}
	return GetNameAndClass(InObject);
}

FString ULogUtilLib::GetNameAndClassScoped(const UObject* const InObject)
{
	check(InObject);
	FString Result;
	Result.Append(TEXT("("));
	Result.Append(GetNameAndClass(InObject));
	Result.Append(TEXT(")"));
	return Result;
}

FString ULogUtilLib::GetYesNo(bool const bYes)
{
	return bYes ? FString(TEXT("YES")) : FString(TEXT("no"));
}