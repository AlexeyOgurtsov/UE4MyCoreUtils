#pragma once

#include "Logging/LogMacros.h"
#include "Log/MyLoggingTypes.h"

/**
* General log: Use this category when you do NOT know what category to use;
*/
DECLARE_LOG_CATEGORY_EXTERN(MyLog, Log, All);

// ~String debug macros Begin
#define M_DEBUG_LOG_POSTFIX (FString(TEXT(" (line: ")) + FString::FromInt(__LINE__) + FString(TEXT(" : ")) + FString(__FILE__) + FString(TEXT(" )")))
#define M_DEBUG_LOG_PREFIX (FString(__FUNCTION__) + FString(TEXT(": "))) 
// ~String debug macros End

// ~Logging macros Begin
#define M_LOG_CUSTOM_TO(LogCategory, LogLevel, FormatString, ...)\
{\
	UE_LOG(LogCategory, LogLevel, TEXT("%s%s%s"),  *M_DEBUG_LOG_PREFIX, *FString::Printf(FormatString, ##__VA_ARGS__), *M_DEBUG_LOG_POSTFIX);\
}

#define M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, LogLevel, FormatString, ...)\
{\
	if(ShouldLog)\
	{\
		M_LOG_CUSTOM_TO(LogCategory, LogLevel, FormatString, ##__VA_ARGS__);\
	}\
}

#define M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, LogLevel, FormatString, ...)\
{\
	if(UMyLoggingTypes::ShouldLogVerbosity(LogFlags, ELogVerbosity::Type::LogLevel))\
	{\
		M_LOG_CUSTOM_TO(LogCategory, LogLevel, FormatString, ##__VA_ARGS__);\
	}\
}

#define M_LOG_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Log, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, Log, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, Log, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERBOSE_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Verbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERBOSE_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, Verbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERBOSE_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, Verbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERY_VERBOSE_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, VerboseVerbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERY_VERBOSE_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, VerboseVerbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERY_VERBOSE_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, VerboseVerbose, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_WARN_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Warning, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_WARN_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, Warning, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_WARN_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, Warning, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_ERROR_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Error, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_ERROR_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, Error, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_ERROR_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, Error, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_FATAL_ERROR_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Fatal, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_FATAL_ERROR_TO_IF(ShouldLog, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF(ShouldLog, LogCategory, Fatal, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_FATAL_ERROR_TO_IF_FLAGS(LogFlags, LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO_IF_FLAGS(LogFlags, LogCategory, Fatal, FormatString, ##__VA_ARGS__);\
}

/**
* Marking body as empty
*/
#define M_EMPTY_TO(LogCategory) {}

/**
* Marking body as empty
*/
#define M_EMPTY_MSG_TO(LogCategory, FormatString, ...) {}

/**
* Fatal non-implemented marking macro.
*/
#define M_NOT_IMPL_MSG_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Error, TEXT("NOT YET IMPL: %s"), *FString::Printf(FormatString, ##__VA_ARGS__));\
	unimplemented();\
}

#define M_NOT_IMPL_MSG_RET_TO(ReturnValue, LogCategory, FormatString, ...)\
{\
	M_NOT_IMPL_MSG_TO(LogCategory, FormatString, ##__VA_ARGS__);\
	return ReturnValue; \
}

/**
* Non fatal non-implementing macro.
*/
#define M_TO_BE_IMPL_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Warning, TEXT("TO BE IMPL: %s"), *FString::Printf(FormatString, ##__VA_ARGS__));\
}

#define M_TO_BE_IMPL_RET_TO(ReturnValue, LogCategory, FormatString, ...)\
{\
	M_TO_BE_IMPL_TO(LogCategory, FormatString, ##__VA_ARGS__);\
	return ReturnValue; \
}

/**
* Message of implemetation note.
*/
#define M_IMPL_NOTE_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Warning, TEXT("TO BE IMPL: %s"), *FString::Printf(FormatString, ##__VA_ARGS__));\
}

/**
* Verifies the return value with CheckExpression and returns the value.
*/
#define M_RETURN_VERIFY(ReturnValue, CheckExpression)\
{\
	verify(CheckExpression);\
	return ReturnValue;\
}

/**
* Verifies the return value with CheckExpression and returns the value.
*/
#define M_RETURN_VERIFY_MSG(ReturnValue, CheckExpression, FormatString, ...)\
{\
	verifyf(CheckExpression, FormatString, ##__VA_ARGS__);\
	return ReturnValue;\
}

/**
* Checks the return value with CheckExpression and returns the value.
*/
#define M_RETURN_CHECK(ReturnValue, CheckExpression)\
{\
	check(CheckExpression);\
	return ReturnValue;\
}

/**
* Checks the return value with CheckExpression and returns the value.
*/
#define M_RETURN_CHECK_MSG(ReturnValue, CheckExpression, FormatString, ...)\
{\
	checkf(CheckExpression, FormatString, ##__VA_ARGS__);\
	return ReturnValue;\
}


#define M_LOG(FormatString, ...)\
{\
	M_LOG_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERBOSE(FormatString, ...)\
{\
	M_LOG_VERBOSE_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_VERBOSE_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_VERBOSE_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_VERBOSE_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_VERBOSE_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_WARN(FormatString, ...)\
{\
	M_LOG_WARN_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_WARN_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_WARN_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_WARN_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_WARN_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_VERY_VERBOSE(FormatString, ...)\
{\
	M_LOG_VERY_VERBOSE_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_VERY_VERBOSE_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_VERY_VERBOSE_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_VERY_VERBOSE_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_VERY_VERBOSE_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_ERROR(FormatString, ...)\
{\
	M_LOG_ERROR_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_ERROR_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_ERROR_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_ERROR_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_ERROR_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_LOG_FATAL_ERROR(FormatString, ...)\
{\
	M_LOG_FATAL_ERROR_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_FATAL_ERROR_IF(ShouldLog, FormatString, ...)\
{\
	M_LOG_FATAL_ERROR_TO_IF(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_FATAL_ERROR_IF_FLAGS(LogFlags, FormatString, ...)\
{\
	M_LOG_FATAL_ERROR_TO_IF_FLAGS(LogFlags, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL_MSG(FormatString, ...)\
{\
	M_NOT_IMPL_MSG_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL()\
{\
	unimplemented();\
}

#define M_TO_BE_IMPL(FormatString, ...)\
{\
	M_TO_BE_IMPL_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_IMPL_NOTE(FormatString, ...)\
{\
	M_IMPL_NOTE_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL_MSG_RET(ReturnValue, FormatString, ...)\
{\
	M_NOT_IMPL_MSG_RET_TO(ReturnValue, MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL_RET(ReturnValue)\
{\
	unimplemented();\
	return ReturnValue;\
}

#define M_TO_BE_IMPL_RET(ReturnValue, FormatString, ...)\
{\
	M_TO_BE_IMPL_RET_TO(ReturnValue, MyLog, FormatString, ##__VA_ARGS__);\
}

/**
* Marking body as empty
*/
#define M_EMPTY() { M_EMPTY_TO(MyLog); }
#define M_EMPTY_MSG(FormatString, ...) { M_EMPTY_MSG_TO(MyLog, FormatString, ##__VA_ARGS__); }

// ~Scoped helpres Begin (@warning: NEVER include implementation in brackets, because it will limit the scope)

#define M_CUSTOM_SCOPED_LOG_HELPER_CLASS_NAME(ClassNamePrefix) FAutogenerated_##ClassNamePrefix##_ScopedLogHelper

/**
* Declares scoped helper class.
*/
#define M_DECLARE_CUSTOM_SCOPED_LOG_HELPER_CLASS_IF(ClassNamePrefix, LogCategory, LogLevel)\
	class M_CUSTOM_SCOPED_LOG_HELPER_CLASS_NAME(ClassNamePrefix)\
	{\
	public:\
		M_CUSTOM_SCOPED_LOG_HELPER_CLASS_NAME(ClassNamePrefix)(bool bInShouldLog, const FString& InPrefixString)\
	:		bShouldLog(bInShouldLog), PrefixString(InPrefixString)\
		{\
			if(bShouldLog)\
			{\
				UE_LOG(LogCategory, LogLevel, TEXT("%s : Block entered"), *PrefixString);\
			}\
		}\
		~M_CUSTOM_SCOPED_LOG_HELPER_CLASS_NAME(ClassNamePrefix)()\
		{\
			if(bShouldLog)\
			{\
				UE_LOG(LogCategory, LogLevel, TEXT("%s : Exiting block"), *PrefixString);\
			}\
		}\
	private:\
		bool bShouldLog;\
		FString PrefixString;\
	};

/**
* Helper class for logging enter/exit of the C++ block.
*/
#define M_SCOPED_LOG_HELPER_CLASS_IF_TO(ClassNamePrefix, LogCategory) M_DECLARE_CUSTOM_SCOPED_LOG_HELPER_CLASS_IF(ClassNamePrefix, LogCategory, Log);

#define M_LOGFUNC_NAMED_STRING_IF_TO(InName, ShouldLog, LogCategory, InString)\
	M_SCOPED_LOG_HELPER_CLASS_IF_TO(InName, LogCategory);\
	M_CUSTOM_SCOPED_LOG_HELPER_CLASS_NAME(InName) Autogenerated_##InName##_ScopedLogHelper {ShouldLog, M_DEBUG_LOG_PREFIX + InString + M_DEBUG_LOG_POSTFIX};

/**
* @note: we disable warning of shadowing local variable, because we often used unnamed log helpers in blocks, and the autogenerated name is the same.
*/
#define M_LOGFUNC_STRING_IF_TO(ShouldLog, LogCategory, InString)\
	__pragma(warning(push))\
	__pragma(warning(disable:4456))\
	M_LOGFUNC_NAMED_STRING_IF_TO(Unnamed, ShouldLog, LogCategory, InString);\
	__pragma(warning(pop))

#define M_LOGFUNC_IF_TO(ShouldLog, LogCategory) M_LOGFUNC_STRING_IF_TO(ShouldLog, LogCategory, FString(TEXT("")));
#define M_LOGFUNC_MSG_IF_TO(ShouldLog, LogCategory, FormatString, ...) M_LOGFUNC_STRING_IF_TO(ShouldLog, LogCategory, *FString::Printf(FormatString, ##__VA_ARGS__));
#define M_LOGBLOCK_IF_TO(ShouldLog, LogCategory, FormatString, ...) M_LOGFUNC_MSG_IF_TO(ShouldLog, LogCategory, FormatString, ##__VA_ARGS__);

#define M_LOGFUNC_STRING_IF_FLAGS_TO(LogFlags, LogCategory, InString) M_LOGFUNC_STRING_IF_TO(UMyLoggingTypes::ShouldLogVerbosity(LogFlags, ELogVerbosity::Type::Log), LogCategory, InString);
#define M_LOGFUNC_IF_FLAGS_TO(LogFlags, LogCategory) M_LOGFUNC_IF_TO(UMyLoggingTypes::ShouldLogVerbosity(LogFlags, ELogVerbosity::Type::Log), LogCategory);
#define M_LOGFUNC_MSG_IF_FLAGS_TO(LogFlags, LogCategory, FormatString, ...) M_LOGFUNC_MSG_IF_TO(UMyLoggingTypes::ShouldLogVerbosity(LogFlags, ELogVerbosity::Type::Log), LogCategory, FormatString, ##__VA_ARGS__);
#define M_LOGBLOCK_IF_FLAGS_TO(LogFlags, LogCategory, FormatString, ...) M_LOGBLOCK_IF_TO(UMyLoggingTypes::ShouldLogVerbosity(LogFlags, ELogVerbosity::Type::Log), LogCategory, FormatString, ##__VA_ARGS__);

#define M_LOGFUNC_TO(LogCategory) M_LOGFUNC_IF_TO(true, LogCategory);
#define M_LOGFUNC_MSG_TO(LogCategory, FormatString, ...) M_LOGFUNC_MSG_IF_TO(true, LogCategory, FormatString, ##__VA_ARGS__);
#define M_LOGBLOCK_TO(LogCategory, FormatString, ...) M_LOGBLOCK_IF_TO(true, LogCategory, FormatString, ##__VA_ARGS__);

#define M_LOGFUNC_STRING_IF(ShouldLog, InString) M_LOGFUNC_STRING_IF_TO(ShouldLog, MyLog, InString);
#define M_LOGFUNC_IF(ShouldLog) M_LOGFUNC_IF_TO(ShouldLog, MyLog);
#define M_LOGFUNC_MSG_IF(ShouldLog, FormatString, ...) M_LOGFUNC_MSG_IF_TO(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);
#define M_LOGBLOCK_IF(ShouldLog, FormatString, ...) M_LOGBLOCK_IF_TO(ShouldLog, MyLog, FormatString, ##__VA_ARGS__);

#define M_LOGFUNC_STRING_IF_FLAGS(LogFlags, InString) M_LOGFUNC_STRING_IF_FLAGS_TO(LogFlags, MyLog, InString);
#define M_LOGFUNC_IF_FLAGS(LogFlags) M_LOGFUNC_IF_FLAGS_TO(LogFlags, MyLog);
#define M_LOGFUNC_MSG_IF_FLAGS(LogFlags, FormatString, ...) M_LOGFUNC_MSG_IF_FLAGS_TO(LogFlags, MyLog, FormatString, ##__VA_ARGS__);
#define M_LOGBLOCK_IF_FLAGS(LogFlags, FormatString, ...) M_LOGBLOCK_IF_FLAGS_TO(LogFlags, MyLog, FormatString, ##__VA_ARGS__);

#define M_LOGFUNC() M_LOGFUNC_TO(MyLog);
#define M_LOGFUNC_MSG(FormatString, ...) M_LOGFUNC_MSG_TO(MyLog, FormatString, ##__VA_ARGS__);
#define M_LOGBLOCK(FormatString, ...) M_LOGBLOCK_TO(MyLog, FormatString, ##__VA_ARGS__);
// ~Scoped helpers End
