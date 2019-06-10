#pragma once

#include "Logging/LogMacros.h"

/**
* General log: Use this category when you do NOT know what category to use;
*/
DECLARE_LOG_CATEGORY_EXTERN(MyLog, Log, All);

/**
* Helper class for logging enter/exit of the C++ block.
*/
class FScopedLogHelper
{
public:
	FScopedLogHelper(const FString& InPrefixString) 
	:	PrefixString(InPrefixString)
	{
		UE_LOG(MyLog, Log, TEXT("%s : Block entered"), *PrefixString);
	}
	~FScopedLogHelper()
	{
		UE_LOG(MyLog, Log, TEXT("%s : Exiting block"), *PrefixString);
	}

private:
	FString PrefixString;
};

// ~String debug macros Begin
#define M_DEBUG_LOGFUNC_PREFIX (FString(__FUNCTION__) + FString(TEXT(":")) + FString::FromInt(__LINE__))
// ~String debug macros End

// ~Logging macros Begin
#define M_LOG_CUSTOM_TO(LogCategory, LogLevel, FormatString, ...)\
{\
	UE_LOG(LogCategory, LogLevel, TEXT("%s: "),  *M_DEBUG_LOGFUNC_PREFIX, *FString::Printf(FormatString, ##__VA_ARGS__));\
}

#define M_LOG_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Log, FormatString);\
}
#define M_LOG_WARN_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Warning, FormatString);\
}
#define M_LOG_ERROR_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Error, FormatString);\
}
#define M_LOG_FATAL_ERROR_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, FatalError, FormatString);\
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
#define M_NOT_IMPL_TO(LogCategory, FormatString, ...)\
{\
	M_LOG_CUSTOM_TO(LogCategory, Error, TEXT("NOT YET IMPL: %s"), *FString::Printf(FormatString, ##__VA_ARGS__));\
	unimplemented();\
}

#define M_NOT_IMPL_RET_TO(ReturnValue, LogCategory, FormatString, ...)\
{\
	M_NOT_IMPL_TO(LogCategory, FormatString, ##__VA_ARGS__);\
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



#define M_LOG(FormatString, ...)\
{\
	M_LOG_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_WARN(FormatString, ...)\
{\
	M_LOG_WARN_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_ERROR(FormatString, ...)\
{\
	M_LOG_ERROR_TO(MyLog, FormatString, ##__VA_ARGS__);\
}
#define M_LOG_FATAL_ERROR(FormatString, ...)\
{\
	M_LOG_FATAL_ERROR_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL(FormatString, ...)\
{\
	M_NOT_IMPL_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_TO_BE_IMPL(FormatString, ...)\
{\
	M_TO_BE_IMPL_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_IMPL_NOTE(FormatString, ...)\
{\
	M_IMPL_NOTE_TO(MyLog, FormatString, ##__VA_ARGS__);\
}

#define M_NOT_IMPL_RET(ReturnValue, FormatString, ...)\
{\
	M_NOT_IMPL_RET_TO(ReturnValue, MyLog, FormatString, ##__VA_ARGS__);\
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
#define M_LOGFUNC() FScopedLogHelper FuncLogHelper {M_DEBUG_LOGFUNC_PREFIX};
#define M_LOGFUNC_MSG(FormatString, ...) FScopedLogHelper FuncLogHelper{M_DEBUG_LOGFUNC_PREFIX + FString(TEXT(": ")) + FString::Printf(FormatString, ##__VA_ARGS__)};
// ~Scoped helpres End

#define M_LOGBLOCK(FormatString, ...) M_LOGFUNC_MSG(FormatString, ##__VA_ARGS__)