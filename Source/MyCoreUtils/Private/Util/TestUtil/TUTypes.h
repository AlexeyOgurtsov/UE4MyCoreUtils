#pragma once

#include "TUTypes.generated.h"

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class ETUFlags : uint8
{
	None                      = 0              UMETA(Hidden),

	ExtLog                    = 1 << 0         UMETA(DisplayName="Extended log"),

	Default                   = None           UMETA(Hidden)
};
ENUM_CLASS_FLAGS(ETUFlags);

USTRUCT(BlueprintType)
struct FTUConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum=ETUFlags), Category = Flags)
	uint8 Flags = static_cast<uint8>(ETUFlags::None);

	ETUFlags GetFlags() const { return static_cast<ETUFlags>(Flags); }
	void SetFlags(ETUFlags InFlags);
	void UnsetFlags(ETUFlags InFlags);
	bool HasAnyFlags(ETUFlags InFlagMask) const;
	bool HasAllFlags(ETUFlags InFlagMask) const;
};
