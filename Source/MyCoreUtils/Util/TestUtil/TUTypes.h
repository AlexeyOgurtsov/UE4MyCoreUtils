#pragma once

#include "TUTypes.generated.h"

UENUM(BlueprintType, Meta=(Bitflags))
enum class ETUFlags : uint8
{
	None                      = 0              UMETA(DisplayName="None"),

	ExtLog                    = 1 << 0         UMETA(DisplayName="Extended log"),

	Default                   = None           UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ETUFlags);

USTRUCT(BlueprintType)
struct FTUConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Flags)
	ETUFlags Flags = ETUFlags::None;

	ETUFlags GetFlags() const { return Flags; }
	void SetFlags(ETUFlags InFlags);
	void UnsetFlags(ETUFlags InFlags);
	bool HasAnyFlags(ETUFlags InFlagMask) const;
	bool HasAllFlags(ETUFlags InFlagMask) const;
};
