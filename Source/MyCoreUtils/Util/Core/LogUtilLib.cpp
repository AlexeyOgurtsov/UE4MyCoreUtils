#include "LogUtilLib.h"

DEFINE_LOG_CATEGORY(MyLog);

ULogUtilLib::ULogUtilLib()
{
}

FString ULogUtilLib::GetNameAndClass(UObject* InObject)
{
	check(InObject);
	TArray<FStringFormatArg> FormatArgs;
	FormatArgs.Add(InObject->GetName());
	FormatArgs.Add(InObject->GetClass()->GetName());
	return FString::Format(TEXT("name=\"{0}\" class=\"{1}\""), FormatArgs);
}

FString ULogUtilLib::GetNameAndClassScoped(UObject* InObject)
{
	check(InObject);
	FString Result;
	Result.Append(TEXT("("));
	Result.Append(GetNameAndClass(InObject));
	Result.Append(TEXT(")"));
	return Result;
}

FString ULogUtilLib::GetYesNo(bool bYes)
{
	return bYes ? FString(TEXT("YES")) : FString(TEXT("no"));
}