#pragma once

#include "Logging/LogMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyLoggingTypes.generated.h"

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class ELogFlags : uint8
{
	None              = 0          UMETA(Hidden),
	LogEverSuccess    = 1 << 0     UMETA(DisplayName="LogEverSuccess", Description="Should we log even successful operations"),
	DisableLog        = 1 << 1     UMETA(DisplayName="DisableLog", Description="Should we disabled ever logging of fails")
};
ENUM_CLASS_FLAGS(ELogFlags);

UCLASS()
class UMyLoggingTypes : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = MyLoggingTypes)
	static void CheckFlagsValid(ELogFlags InFlags);

	UFUNCTION(BlueprintPure, Category = MyLoggingTypes)
	static bool AreFlagsValid(ELogFlags InFlags);

	UFUNCTION(BlueprintPure, Category = MyLoggingTypes)
	static bool ShouldLog(ELogFlags InFlags, bool bErrorOrWarn);

	static bool ShouldLogVerbosity(ELogFlags InFlags, ELogVerbosity::Type InVerbosity);
	static bool IsVerbosityWarnOrError(ELogVerbosity::Type InVerbosity);
};
