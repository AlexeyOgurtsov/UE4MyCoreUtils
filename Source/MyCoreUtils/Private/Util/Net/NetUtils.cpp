#include "NetUtils.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "Algo/Transform.h"
#include "Engine/World.h"
#include "Util/Core/LogUtilLib.h"


void UNetUtils::LogComponentNetVars(const UActorComponent* const Component)
{
	checkf(Component, TEXT("When calling \"%s\" passed actor must be valid NON-null poitner"), TEXT(__FUNCTION__));

	M_LOGFUNC();
	
	NetPrefixedLog(Component, TEXT(__FUNCTION__), TEXT(""), {}, ENetLogFlags::All);
}

void UNetUtils::LogNetVars(const AActor* const Actor)
{
	checkf(Actor, TEXT("When calling \"%s\" passed actor must be valid NON-null poitner"), TEXT(__FUNCTION__));

	M_LOGFUNC();
	NetPrefixedLog(Actor, TEXT(__FUNCTION__), TEXT(""), {}, ENetLogFlags::All);
	
	ULogUtilLib::LogInt32C(TEXT("NetTag"), Actor->NetTag);

	ULogUtilLib::LogYesNoC(GET_MEMBER_NAME_STRING_CHECKED(AActor, bAlwaysRelevant), Actor->bAlwaysRelevant);
	ULogUtilLib::LogYesNoC(GET_MEMBER_NAME_STRING_CHECKED(AActor, bOnlyRelevantToOwner), Actor->bOnlyRelevantToOwner);
	ULogUtilLib::LogYesNoC(GET_MEMBER_NAME_STRING_CHECKED(AActor, bNetUseOwnerRelevancy), Actor->bNetUseOwnerRelevancy);
	ULogUtilLib::LogYesNoC(GET_MEMBER_NAME_STRING_CHECKED(AActor, bRelevantForNetworkReplays), Actor->bRelevantForNetworkReplays);

	ULogUtilLib::LogFloatC(GET_MEMBER_NAME_STRING_CHECKED(AActor, NetCullDistanceSquared), Actor->NetCullDistanceSquared);

	ULogUtilLib::LogYesNoC(GET_FUNCTION_NAME_STRING_CHECKED(AActor, IsReplicatingMovement), Actor->IsReplicatingMovement());
	ULogUtilLib::LogYesNoC(GET_FUNCTION_NAME_STRING_CHECKED(AActor, NeedsLoadForClient), Actor->NeedsLoadForClient());
	ULogUtilLib::LogFloatC(GET_MEMBER_NAME_STRING_CHECKED(AActor, NetUpdateFrequency), Actor->NetUpdateFrequency);
	ULogUtilLib::LogFloatC(GET_MEMBER_NAME_STRING_CHECKED(AActor, MinNetUpdateFrequency), Actor->MinNetUpdateFrequency);
	ULogUtilLib::LogNameC(GET_FUNCTION_NAME_STRING_CHECKED(AActor, GetNetDriverName), Actor->GetNetDriverName());

	if(const AController* Controller = Cast<AController>(Actor))
	{
		LogNetVars_ControllerPart(Controller);
	}
	else if(const APawn* Pawn = Cast<APawn>(Actor))
	{
		LogNetVars_PawnPart(Pawn);
	}
	// @TODO: Physics body etc.
}

void UNetUtils::LogNetVars_ControllerPart(const AController* const Controller)
{
	// @TODO
	if(const APlayerController* PC = Cast<APlayerController>(Controller))
	{
		LogNetVars_PlayerControllerPart(PC);
	}
	else if(const AAIController* AIController = Cast<AAIController>(Controller))
	{
		LogNetVars_AIControllerPart(AIController);
	}
}

void UNetUtils::LogNetVars_PlayerControllerPart(const APlayerController* const PC)
{
	// @TODO
	//ULogUtilLib::LogNameC(TEXT("bReplicateInstigator"), PC->bReplicateInstigator);
}

void UNetUtils::LogNetVars_AIControllerPart(const AAIController* const AIController)
{
	// @TODO
	//ULogUtilLib::LogNameC(TEXT("bReplicateInstigator"), PC->bReplicateInstigator);
}

void UNetUtils::LogNetVars_PawnPart(const APawn* const Pawn)
{
	// @TODO
	if(const ACharacter* Character = Cast<ACharacter>(Pawn))
	{
		LogNetVars_CharacterPart(Character);
	}
}

void UNetUtils::LogNetVars_CharacterPart(const ACharacter* const Actor)
{
	// @TODO
}

void UNetUtils::K2_NetLogf(const AActor* const Actor, const FString& Format, const TArray<FString>& Args, ENetLogFlags const LogFlags)
{
	TArray<FStringFormatArg> FormatArgs;
	Algo::Transform
	(
	 	Args, FormatArgs, 
		[](const FString& S) 
		{ 
			return FStringFormatArg { S }; 
		} 
	);
	return NetLog(Actor, *Format, FormatArgs, LogFlags);
}

void UNetUtils::K2_NetLogString(const AActor* const Actor, const FString& String, ENetLogFlags const LogFlags)
{
	return NetLog(Actor, TEXT("{0}"), {FStringFormatArg{String}}, LogFlags);
}

void UNetUtils::NetLog(const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG(TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetLogIf(bool const bShouldLog, const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLog(const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG(TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogIf(bool const bShouldLog, const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetLogError(const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_ERROR(TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetLogErrorIf(bool const bShouldLog, const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_ERROR_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogError(const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_ERROR(TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogErrorIf(bool const bShouldLog, const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_ERROR_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetLogWarn(const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_WARN(TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetLogWarnIf(const bool bShouldLog, const AActor* const Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_WARN_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Actor, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogWarn(const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_WARN(TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogWarnIf(const bool bShouldLog, const AActor* const Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	M_LOG_WARN_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Actor, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetLog(const UActorComponent* Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags)
{
	M_LOG(TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetLogIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags)
{
	M_LOG_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLog(const UActorComponent* const Comp, const TCHAR* Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG(TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetLogError(const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_ERROR(TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetLogErrorIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_ERROR_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogError(const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_ERROR(TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogErrorIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_ERROR_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetLogWarn(const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_WARN(TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetLogWarnIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_WARN_IF(bShouldLog, TEXT("%s"), *NetLogFormat(Comp, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogWarn(const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_WARN(TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

void UNetUtils::NetPrefixedLogWarnIf(const bool bShouldLog, const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	M_LOG_WARN_IF(bShouldLog, TEXT("%s"), *NetPrefixedLogFormat(Comp, Prefix, Format, Args, LogFlags));
}

FString UNetUtils::NetLogFormat(const AActor* const Actor, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	return FString::Format
	(
		TEXT("T={0};obTm={1}; {2}: {3}"),
		{
			FStringFormatArg(Actor && Actor->GetWorld() ? *FString::SanitizeFloat(Actor->GetWorld()->GetTimeSeconds()) : FString(TEXT("{NULL ACT}"))),
			FStringFormatArg(Actor && Actor->GetWorld() ? *FString::SanitizeFloat(Actor->GetGameTimeSinceCreation()) : FString(TEXT("{NULL ACT}"))),
			FStringFormatArg(GetLogPrefix(Actor, LogFlags)),
			FStringFormatArg(FString::Format(Format, Args))
		}
	);
}

FString UNetUtils::NetPrefixedLogFormat(const AActor* const Actor, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	return FString(Prefix) + FString(TEXT(": ")) + NetLogFormat(Actor, Format, Args, LogFlags);
}

FString UNetUtils::NetLogFormat(const UActorComponent* const Comp, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	FString ComponentPrefix = TEXT(""); 
	if( Comp )
	{
		if((LogFlags & ENetLogFlags::LogIsReplicated) != ENetLogFlags::None)
		{
			AppendComponentIsReplicatedToLogString(ComponentPrefix, Comp);
		}

		if((LogFlags & ENetLogFlags::LogNetMode) != ENetLogFlags::None)
		{
			AppendNetModeToLogString(ComponentPrefix, Comp->GetNetMode());
		}
	}
	else
	{
		ComponentPrefix = TEXT("NULL COMP");
	}
	return NetPrefixedLogFormat(Comp ? Comp->GetOwner() : nullptr, *ComponentPrefix, Format, Args, LogFlags);
}

FString UNetUtils::NetPrefixedLogFormat(const UActorComponent* const Comp, const TCHAR* const Prefix, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, const ENetLogFlags LogFlags)
{
	return FString(Prefix) + FString(TEXT(": ")) + NetLogFormat(Comp, Format, Args, LogFlags);
}

FString UNetUtils::GetLogPrefix(const AActor* const Actor, ENetLogFlags const LogFlags)
{
	if (Actor == nullptr)
	{
		return FString(TEXT("nullptr"));
	}

	FString ResultString;

	if((LogFlags & ENetLogFlags::LocalRole) != ENetLogFlags::None)
	{
		ResultString.Append(FString::Printf(TEXT(";%s"), *GetRoleString(Actor->GetLocalRole())));
	}

	if((LogFlags & ENetLogFlags::RemoteRole) != ENetLogFlags::None)
	{
		ResultString.Append(FString::Printf(TEXT(";REMOT=%s"), *GetRoleString(Actor->GetRemoteRole())));
	}

	if((LogFlags & ENetLogFlags::LogHasAuthority) != ENetLogFlags::None)
	{
		if(Actor->HasAuthority())
		{
			ResultString.Append(TEXT(";HAS_AUTH"));
		}
	}

	if ((LogFlags & ENetLogFlags::Owner) != ENetLogFlags::None)
	{
		AppendOwnerToLogString(ResultString, Actor);
	}

	if ((LogFlags & ENetLogFlags::LogNetOwner) != ENetLogFlags::None)
	{
		AppendNetOwnerToLogString(ResultString, Actor);
	}

	if ((LogFlags & ENetLogFlags::Instigator) != ENetLogFlags::None)
	{
		AppendInstigatorToLogString(ResultString, Actor);
	}

	if ((LogFlags & ENetLogFlags::LogIsReplicated) != ENetLogFlags::None)
	{
		AppendIsReplicatedToLogString(ResultString, Actor);
	}

	if ((LogFlags & ENetLogFlags::LogNetMode) != ENetLogFlags::None)
	{
		AppendNetModeToLogString(ResultString, Actor->GetNetMode());
	}

	return ResultString;
}

FString UNetUtils::GetNetModeString(ENetMode const NetMode)
{
	switch(NetMode)
	{
	case NM_Standalone:
		return FString(TEXT("NMStandalone"));

	case NM_DedicatedServer:
		return FString(TEXT("NMDedicServ"));

	case NM_ListenServer:
		return FString(TEXT("NMListenServ"));

	case NM_Client:
		return FString(TEXT("NMClient"));

	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

FString UNetUtils::GetRoleString(ENetRole const Role)
{
	switch(Role)
	{
	case ROLE_None:
		return FString(TEXT("Non"));
	case ROLE_SimulatedProxy:
		return FString(TEXT("SimProx"));
	case ROLE_AutonomousProxy:
		return FString(TEXT("AutoProx"));
	case ROLE_Authority:
		return FString(TEXT("AUTH"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

FString UNetUtils::GetDormancyString(ENetDormancy const Dormancy)
{
	switch(Dormancy)
	{
	case DORM_Never:
		return FString(TEXT("NEV"));
	case DORM_Awake:
		return FString(TEXT("AWK"));
	case DORM_DormantAll:
		return FString(TEXT("DrAll"));
	case DORM_DormantPartial:
		return FString(TEXT("DrPart"));
	case DORM_Initial:
		return FString(TEXT("DrIni"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

FString UNetUtils::GetOwnerString(const AActor* const Actor)
{
	if (Actor == nullptr)
	{
		return TEXT("{Actor is nullptr}");
	}
	else
	{
		return ULogUtilLib::GetNameAndClassSafe(Actor->GetOwner());
	}
}

FString UNetUtils::GetNetOwnerString(const AActor* const Actor) 
{
	if (Actor == nullptr)
	{
		return TEXT("{Actor is nullptr}");
	}
	else
	{
		return ULogUtilLib::GetNameAndClassSafe(Actor->GetNetOwner());
	}
}

void UNetUtils::AppendNetModeToLogString(FString& S, ENetMode const NM)
{
	S.Append(GetNetModeString(NM));
}

void UNetUtils::AppendOwnerToLogString(FString& S, const AActor* const Actor)
{
	S.Append
	(
		FString::Format
		(
			TEXT(";Owner={0}"), 
			{
				GetOwnerString(Actor) 
			}
		)
	);
}

void UNetUtils::AppendNetOwnerToLogString(FString& S, const AActor* const Actor)
{
	S.Append
	(
		FString::Format
		(
			TEXT(";NetOwner={0}"),
			{
				GetNetOwnerString(Actor)
			}
		)
	);
}

FString UNetUtils::GetInstigatorString(const AActor* const Actor)
{
	if (Actor == nullptr)
	{
		return TEXT("{Actor is nullptr}");
	}
	else
	{
		return ULogUtilLib::GetNameAndClassSafe(Actor->GetInstigator());
	}
}

FString UNetUtils::GetIsReplicatedString(const AActor* const Actor)
{
	if (Actor == nullptr)
	{
		return TEXT("{Actor is nullptr}");
	}
	else
	{
		return Actor->GetIsReplicated() ? FString(TEXT("YES")) : FString(TEXT("no"));
	}
}

FString UNetUtils::GetComponentIsReplicatedString(const UActorComponent* Comp)
{
	if (Comp == nullptr)
	{
		return TEXT("{Actor is nullptr}");
	}
	else
	{
		return Comp->GetIsReplicated() ? FString(TEXT("YES")) : FString(TEXT("no"));
	}
}

void UNetUtils::AppendInstigatorToLogString(FString& S, const AActor* const Actor)	
{
	S.Append
	(
		FString::Format
		(
			TEXT(";Instigator={0}"), 
			{
				GetInstigatorString(Actor) 
			}
		)
	);
}

void UNetUtils::AppendIsReplicatedToLogString(FString& S, const AActor* const Actor)	
{
	S.Append
	(
		FString::Format
		(
			TEXT(";IsReplicated={0}"), 
			{
				GetIsReplicatedString(Actor) 
			}
		)
	);
}

void UNetUtils::AppendComponentIsReplicatedToLogString(FString& S, const UActorComponent* const Comp)
{
	S.Append
	(
		FString::Format
		(
			TEXT(";IsReplicated={0}"), 
			{
				GetComponentIsReplicatedString(Comp) 
			}
		)
	);
}
