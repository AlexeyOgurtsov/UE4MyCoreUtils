#include "MyLoggingTypes.h"

bool UMyLoggingTypes::ShouldLog(ELogFlags InFlags, bool bErrorOrWarn)
{
	CheckFlagsValid(InFlags);
	if(bErrorOrWarn) { return true; }
	return ELogFlags::None == (InFlags & ELogFlags::DisableLog);
}

bool UMyLoggingTypes::ShouldLogVerbosity(ELogFlags InFlags, ELogVerbosity::Type InVerbosity)
{
	CheckFlagsValid(InFlags);
	bool const bWarnOrError = IsVerbosityWarnOrError(InVerbosity);
	return ShouldLog(InFlags, bWarnOrError);
}

bool UMyLoggingTypes::AreFlagsValid(ELogFlags InFlags)
{
	ELogFlags constexpr MASK = ELogFlags::LogEverSuccess | ELogFlags::DisableLog;
	if(MASK == (InFlags & MASK))
	{		
		// Setting up both "log ever success" and "disable log" flags is prohibited
		// because of ambiguity (what flag is superior?)
		return false;
	}		
	return true;
}

void UMyLoggingTypes::CheckFlagsValid(ELogFlags InFlags)
{
	checkf(AreFlagsValid(InFlags), TEXT("Log flags must be valid"));
}

bool UMyLoggingTypes::IsVerbosityWarnOrError(ELogVerbosity::Type InVerbosity)
{
	switch(InVerbosity)
	{
	case ELogVerbosity::Type::Fatal:
	case ELogVerbosity::Type::Error:
	case ELogVerbosity::Type::Warning:
		return true;

	default:
		return false;
	}
	checkNoEntry();
}