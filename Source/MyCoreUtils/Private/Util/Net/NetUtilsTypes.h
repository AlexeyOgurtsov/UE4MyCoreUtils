#pragma once

#include "NetUtilsTypes.generated.h"

/** ENetLogFlags*/
UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"), Category="Log|Net")
enum class ENetLogFlags : uint8
{
	/** None*/
	None = 0 UMETA(DisplayName="None")
	
	/** LocalRole*/
	, LocalRole = 1 << 0 UMETA(DisplayName="LocalRole")

	/** RemoteRole*/
	, RemoteRole = 1 << 1 UMETA(DisplayName="RemoteRole")

	/** Dormancy*/
	, Dormancy = 1 << 2 UMETA(DisplayName="Dormancy")

	/** Dormancy*/
	, LogHasAuthority = 1 << 3 UMETA(DisplayName="LogHasAuthority")

	/** Owner*/
	, Owner = 1 << 4 UMETA(DisplayName = "Owner")
	
	/** Default*/
	, Default = LocalRole | RemoteRole | LogHasAuthority UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ENetLogFlags);
