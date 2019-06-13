#pragma once

#include "Logging/LogMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "XprUtilLib.generated.h"

UCLASS()
class UXprUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Logs FString into the given log category.
	*/
	static void LogByCategory(const FLogCategoryBase& InLogCategory, ELogVerbosity::Type InVerbosity, const FString& InString);
};