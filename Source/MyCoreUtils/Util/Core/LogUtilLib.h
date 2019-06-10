#pragma once

#include "LogUtilLib.generated.h"

/**
* General log: Use this category when you do NOT know what category to use;
*/
DECLARE_LOG_CATEGORY_EXTERN(MyLog, Log, All);

/**
* Helper class for logging enter/exit of the C++ block.
*/
class FScopedLogHelper
{
public:
	FScopedLogHelper(const FString& InPrefixString) 
	:	PrefixString(InPrefixString)
	{
		UE_LOG(MyLog, Log, TEXT("%s : Block entered"), *PrefixString);
	}
	~FScopedLogHelper()
	{
		UE_LOG(MyLog, Log, TEXT("%s : Exiting block"), *PrefixString);
	}

private:
	FString PrefixString;
};

// ~String debug macros Begin
#define DEBUG_LOGFUNC_PREFIX FString(__FUNCTION__) + FString(TEXT(":")) + FString::FromInt(__LINE__)
// ~String debug macros End

// ~Logging macros Begin
#define LOGFUNC() FScopedLogHelper FuncLogHelper {DEBUG_LOGFUNC_PREFIX};
#define LOGFUNC_MSG(InMessage) FScopedLogHelper FuncLogHelper{DEBUG_LOGFUNC_PREFIX + FString(TEXT(":")) + InMessage};

// ~Logging macros End

UCLASS()
class ULogUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	ULogUtilLib();

	/**
	* Returns name and class of the object.
	* WARNING: Object may NOT be nullptr
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClass(UObject* InObject);

	/**
	* Returns name and class of the object, enclosed in brackets.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassScoped(UObject* InObject);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetYesNo(bool bYes);
};