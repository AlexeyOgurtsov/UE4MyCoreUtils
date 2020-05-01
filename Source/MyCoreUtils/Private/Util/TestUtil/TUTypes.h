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
struct FTURenderDebugBoundsProps
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bShouldRender = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool bConsiderOnlyCollidingComponents = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	FColor Color = FColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	uint8 DepthPriority = 0.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	float Thickness = 3.0F;
};

USTRUCT(BlueprintType)
struct FTUConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	FTURenderDebugBoundsProps RenderDebugBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(Bitmask, BitmaskEnum=ETUFlags), Category = Flags)
	uint8 Flags = static_cast<uint8>(ETUFlags::None);

	ETUFlags GetFlags() const { return static_cast<ETUFlags>(Flags); }
	void SetFlags(ETUFlags InFlags);
	void UnsetFlags(ETUFlags InFlags);
	bool HasAnyFlags(ETUFlags InFlagMask) const;
	bool HasAllFlags(ETUFlags InFlagMask) const;
};
