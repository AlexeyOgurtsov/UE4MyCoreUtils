#pragma once

#include "Util\Core\Log\MyLoggingTypes.h"
#include "PhysUtilLibTypes.generated.h"

UENUM(BlueprintType, Meta=(BitFlags, UseEnumValuesAsMaskValuesInEditor = "true"))
enum class ELogHitFlags : uint8
{
	None                          = 0 UMETA(DisplayName = "None"),

	LeanAndMeanOwner              = 1 << 0                                              UMETA(DisplayName = "LeanAndMean Owner"),
	LeanAndMeanLocation           = 1 << 1                                              UMETA(DisplayName = "LeanAndMean Location"),
	LeanAndMean                   = LeanAndMeanOwner | LeanAndMeanLocation              UMETA(DisplayName = "LeanAndMean"),

	Default                       = None                                                UMETA(DisplayName = "Default")
};
ENUM_CLASS_FLAGS(ELogHitFlags);
