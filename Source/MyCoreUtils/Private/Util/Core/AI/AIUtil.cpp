#include "AIUtil.h"
#include "Util/Core/LogUtilLib.h"

UAIUtil::UAIUtil()
{
}

FString UAIUtil::GetPathFollowingRequestResultString(EPathFollowingRequestResult::Type Code)
{
	switch(Code)
	{
	case EPathFollowingRequestResult::Type::Failed:
		return FString(TEXT("Failed"));
	case EPathFollowingRequestResult::Type::AlreadyAtGoal:
		return FString(TEXT("AlreadyAtGoal"));
	case EPathFollowingRequestResult::Type::RequestSuccessful:
		return FString(TEXT("RequestSuccessful"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

void UAIUtil::LogPathFollowingRequestResult(const FString& InKey, const EPathFollowingRequestResult::Type Code)
{
	ULogUtilLib::LogString(InKey, GetPathFollowingRequestResultString(Code));
}

FString UAIUtil::GetPathFollowingResultString(EPathFollowingResult::Type Code)
{
	switch(Code)
	{
	case EPathFollowingResult::Type::Success:
		return FString(TEXT("Success"));
	case EPathFollowingResult::Type::Blocked:
		return FString(TEXT("Blocked"));
	case EPathFollowingResult::Type::OffPath:
		return FString(TEXT("OffPath"));
	case EPathFollowingResult::Type::Aborted:
		return FString(TEXT("Aborted"));
	case EPathFollowingResult::Type::Skipped_DEPRECATED:
		return FString(TEXT("Skipped_DEPRECATED"));
	case EPathFollowingResult::Type::Invalid:
		return FString(TEXT("Invalid"));
	default:
		break;
	}
	return FString(TEXT("Unknown"));
}

FString UAIUtil::GetPathFollowingResultFlagsString(FPathFollowingResultFlags::Type const InFlags)
{
	FString Result;
	if((InFlags & FPathFollowingResultFlags::Success) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|Success"));
	}  
	if((InFlags & FPathFollowingResultFlags::Blocked) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|Blocked"));
	}  
	if((InFlags & FPathFollowingResultFlags::OffPath) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|OffPath"));
	}  
	if((InFlags & FPathFollowingResultFlags::UserAbort) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|UserAbort"));
	}  
	if((InFlags & FPathFollowingResultFlags::OwnerFinished) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|OwnerFinished"));
	}  
	if((InFlags & FPathFollowingResultFlags::InvalidPath) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|InvalidPath"));
	}  
	if((InFlags & FPathFollowingResultFlags::MovementStop) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|MovementStop"));
	}  
	if((InFlags & FPathFollowingResultFlags::NewRequest) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|NewRequest"));
	}  
	if((InFlags & FPathFollowingResultFlags::ForcedScript) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|ForcedScript"));
	}  
	if((InFlags & FPathFollowingResultFlags::AlreadyAtGoal) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|AlreadyAtGoal"));
	}  
	if((InFlags & FPathFollowingResultFlags::FirstGameplayFlagShift) != FPathFollowingResultFlags::None)
	{
		Result += FString(TEXT("|FirstGameplayFlagShift"));
	}  
	return Result;
}

void UAIUtil::LogPathFollowingResultCode(const FString& InKey, EPathFollowingResult::Type const Code)
{
	ULogUtilLib::LogString(InKey, GetPathFollowingResultString(Code));
}

void UAIUtil::LogPathFollowingResult(const FString& InKey, const FPathFollowingResult& Result)
{
	M_LOG(TEXT("%s: logging PathFollowingResult"), *InKey);
	// NOTE: ToString() implementation requires extra module include (AIModule)
	//M_LOG(TEXT("ToString: %s"), *Result.ToString());
	LogPathFollowingResultCode(TEXT("Code"), Result.Code);
	LogPathFollowingResultFlags(TEXT("Flags"), Result.Flags);
}
void UAIUtil::LogPathFollowingResultFlags(const FString& InKey, FPathFollowingResultFlags::Type const InFlags)
{
	ULogUtilLib::LogString(InKey, GetPathFollowingResultFlagsString(InFlags));
}
