#pragma once

#include "MyObjectCreationTypes.generated.h"


/** EMyObjectCreationFlags*/
UENUM(BlueprintType, Category=ObjectCreation, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class EMyObjectCreationFlags : uint8
{
	None = 0 UMETA(Hidden)
	
	/** Dynamic: created not within constructor or construction script*/
	, Dynamic = 1 << 0 UMETA(DisplayName="Dynamic")
};
ENUM_CLASS_FLAGS(EMyObjectCreationFlags);

