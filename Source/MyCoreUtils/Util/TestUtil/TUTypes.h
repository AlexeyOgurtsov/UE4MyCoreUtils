#pragma once

#include "TUTypes.generated.h"

UENUM(BlueprintType)
enum class ETUFlags : uint8
{
	None                      = 0              UMETA(DisplayName="None"),

	ExtLog                    = 1 << 0         UMETA(DisplayName="Extended log"),

	Default                   = None           UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ETUFlags);