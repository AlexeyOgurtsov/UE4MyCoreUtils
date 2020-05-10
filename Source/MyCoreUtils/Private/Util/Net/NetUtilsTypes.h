#pragma once

#include "NetUtilsTypes.generated.h"

/** ENetLogFlags*/
UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"), Category="Log|Net")
enum class ENetLogFlags : uint8
{
	/** None*/
	None = 0 UMETA(DisplayName="None")
	
	/** LocalRole*/
	, LocalRole = 1 << 0 UMETA(DisplayName="Local Role")

	/** RemoteRole*/
	, RemoteRole = 1 << 1 UMETA(DisplayName="Remote Role")

	/** Dormancy*/
	, Dormancy = 1 << 2 UMETA(DisplayName="Dormancy")

	/** Dormancy*/
	, LogHasAuthority = 1 << 3 UMETA(DisplayName="Log Has Authority")

	/** Owner*/
	, Owner = 1 << 4 UMETA(DisplayName = "Owner")

	/** Instigator*/
	, Instigator = 1 << 5 UMETA(DisplayName = "Instigator")

	/** LogIsReplicated*/
	, LogIsReplicated = 1 << 6 UMETA(DisplayName = "Log Is Replicated")

	/** LogNetMode*/
	, LogNetMode = 1 << 7 UMETA(DisplayName = "Log Net Mode")

	/** LogNetOwner*/
	, LogNetOwner = Owner UMETA(DisplayName = "Log Net Owner")

	/** Default*/
	, All = LocalRole | RemoteRole 
		| Dormancy 
		| LogHasAuthority | Owner | Instigator
	    | LogIsReplicated 
		| LogNetMode
		| LogNetOwner
		UMETA(DisplayName="All")
	
	/** Default*/
	, Default = LocalRole | RemoteRole | LogHasAuthority | LogNetMode | LogNetOwner UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ENetLogFlags);
