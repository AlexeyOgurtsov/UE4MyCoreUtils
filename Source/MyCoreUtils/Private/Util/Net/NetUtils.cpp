#include "NetUtils.h"
#include "GameFramework\Actor.h"
#include "Algo\Transform.h"
#include "Util\Core\LogUtilLib.h"

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

FString UNetUtils::NetLogFormat(const AActor* const Actor, const TCHAR* const Format, const TArray<FStringFormatArg>& Args, ENetLogFlags const LogFlags)
{
	return FString::Format
	(
		TEXT("{0}: {1}"), 
		{
			FStringFormatArg(GetLogPrefix(Actor, LogFlags)),
			FStringFormatArg(FString::Format(Format, Args))
		}
	);
}

FString UNetUtils::NetPrefixedLogFormat(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags)
{
	return FString(Prefix) + FString(TEXT(": ")) + NetLogFormat(Actor, Format, Args, LogFlags);
}

FString UNetUtils::GetLogPrefix(const AActor* const Actor, ENetLogFlags const LogFlags)
{
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

	return ResultString;
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
