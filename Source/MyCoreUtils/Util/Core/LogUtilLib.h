#pragma once

#include "MyDebugMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextProperty.h"
#include "LogUtilLib.generated.h"

/**
* @TODO Array utils:
* 1. Should take UObject-derived classes also!
*/

UENUM(BlueprintType)
enum class EMyLogObjectFlags : uint8
{
	None UMETA(DisplayName="None"),

	SuppressNameAndClass         = 1 << 0    UMETA(DisplayName="Suppress name and class"),

	InternalObjectFlags          = 1 << 1    UMETA(DisplayName="Internal object flags"),
	ObjectFlags                  = 1 << 2    UMETA(DisplayName="Object flags"),

	FullGroupName                = 1 << 3    UMETA(DisplayName="Full group name"),
	Outer                        = 1 << 4    UMETA(DisplayName="Outer"),

	Full                         = InternalObjectFlags | ObjectFlags | Outer | FullGroupName UMETA(DisplayName="Full"), // Provide maximal info when logging

	Default                      = ObjectFlags | Outer UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(EMyLogObjectFlags);

UENUM()
enum class ELogRangeFlags : uint8
{
	None                       = 0            UMETA(DisplayName="None"),

	LogSummary                 = 1 << 0       UMETA(DisplayName="Log summary"),
	LogIndex                   = 1 << 1       UMETA(DisplayName="Log index"),

	/**
	* If set, extended object according to flags will be performed for each object in the range,
	* otherwise only name and class are to be logged.
	*/
	ExtObjectLog               = 1 << 2       UMETA(DisplayName="Ext object log"),

	/**
	* If possible, all elements of the range and summary is to be logged on the same line
	*/
	OneLine                    = 1 << 3       UMETA(DisplayName="One line"),

	Default                    = LogSummary | LogIndex            UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ELogRangeFlags);

UCLASS()
class ULogUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	ULogUtilLib();

	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is invalid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClass(const UObject* InObject);

	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is valid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassSafe(const UObject* InObject);

	/**
	* Returns name and class of the object, enclosed in brackets.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassScoped(const UObject* InObject);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyedNameAndClass(const FString& InKey, const UObject* InObject);
	static FString GetKeyedNameAndClassC(const TCHAR* InKey, const UObject* InObject);


	// ~Range logging Begin
	/**
	* @see: LogObjectRange
	*/
	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogObjectSet"))
	static int32 K2LogObjectSet
	(
		const TSet<UObject*>& InSet, 
		ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InSet, InFlags, InLogObjectFlags);
	}

	/**
	* @see: LogObjectRange
	*/
	static int32 LogObjectSet
	(
		const TSet<UObject*>& InSet, 
		ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InSet, InFlags, InLogObjectFlags);
	}

	/**
	* @see: LogObjectRange
	*/
	static int32 LogObjectSet
	(
		const TSet<const UObject*>& InSet, 
		ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InSet, InFlags, InLogObjectFlags);
	}

	/**
	* @see: LogObjectRange
	*/
	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogObjectArray"))
	static int32 K2LogObjectArray
	(
		const TArray<UObject*>& InArray,
	       	ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InArray, InFlags, InLogObjectFlags);
	}

	/**
	* @see: LogObjectRange
	*/
	static int32 LogObjectArray
	(
		const TArray<UObject*>& InArray,
	       	ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InArray, InFlags, InLogObjectFlags);
	}

	static int32 LogObjectArray
	(
		const TArray<const UObject*>& InArray,
	       	ELogRangeFlags const InFlags = ELogRangeFlags::Default,
	       	EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		return LogObjectRange(InArray, InFlags, InLogObjectFlags);
	}

	/**
	* Logs all objects from the given range.
	*
	* @param: TRange: container of const UObject-derived pointers*
	* @returns: count of objects in the range.
	*/
	template<class TRange>
	static int32 LogObjectRange
	(
		const TRange& InRange, 
		ELogRangeFlags const InFlags = ELogRangeFlags::Default, 
		EMyLogObjectFlags const InLogObjectFlags = EMyLogObjectFlags::Default
	)
	{
		M_LOGFUNC()
		int32 Index = 0;
		bool const bShouldLogSummary = (InFlags & ELogRangeFlags::LogSummary) != ELogRangeFlags::None;
		bool const bLogIndex = (InFlags & ELogRangeFlags::LogIndex) != ELogRangeFlags::None;
		bool const bExtObjectLog = (InFlags & ELogRangeFlags::ExtObjectLog) != ELogRangeFlags::None;

		for(TRange::ElementType Obj : InRange)
		{
			if(Obj == nullptr)
			{
				if(bLogIndex)
				{
					M_LOG(TEXT("%d: nullptr"), Index);
				}
				else
				{
					M_LOG(TEXT("nullptr"));
				}
			}
			else
			{
				if(bExtObjectLog)
				{
					LogObjectSafe(Obj, InLogObjectFlags);
				}
				else
				{
					if(bLogIndex)
					{
						M_LOG(TEXT("%d: {%s}"), Index, *GetNameAndClassSafe(Obj));
					}
					else
					{
						M_LOG(TEXT("{%s}"), Index, *GetNameAndClassSafe(Obj));
					}
				}
			}
			Index++;
		}

		if(bShouldLogSummary)
		{
			M_LOG(TEXT("Total %d objects logged"), Index);
		}

		return Index;
	}
	// ~Range logging End

	// ~Value logging Begin
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameClassSafe(const UObject* InObject);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogKeyedNameClassSafe(const FString& InKey, const UObject* InObject);
	static void LogKeyedNameClassSafeC(const TCHAR* InKey, const UObject* InObject);
	
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetYesNo(bool bYes);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyYesNo(const FString& InKey, bool bInValue);
	static FString GetKeyYesNoC(const TCHAR* InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNo(const FString& InKey, bool bInValue);
	static void LogYesNoC(const TCHAR* InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNoIf(bool bInShouldLog, const FString& InKey, bool bInValue);
	static void LogYesNoIfC(bool bInShouldLog, const TCHAR* InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogYesNoIfFlags(ELogFlags InLogFlags, const FString& InKey, bool bInValue);
	static void LogYesNoIfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, bool bInValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloat(const FString& InKey, float InValue);
	static void LogFloatC(const TCHAR* InKey, float InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloatIf(bool bInShouldLog, const FString& InKey, float InValue);
	static void LogFloatIfC(bool bInShouldLog, const TCHAR* InKey, float InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogFloatIfFlags(ELogFlags InFlags, const FString& InKey, float InValue);
	static void LogFloatIfFlagsC(ELogFlags InFlags, const TCHAR* InKey, float InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyFloat(const FString& InKey, float InValue);
	static FString GetKeyFloatC(const TCHAR* InKey, float InValue);

	static void LogDouble(const FString& InKey, double InValue);
	static void LogDoubleC(const TCHAR* InKey, double InValue);
	static void LogDoubleIf(bool bInShouldLog, const FString& InKey, double InValue);
	static void LogDoubleIfC(bool bInShouldLog, const TCHAR* InKey, double InValue);
	static void LogDoubleIfFlags(ELogFlags InFlags, const FString& InKey, double InValue);
	static void LogDoubleIfFlagsC(ELogFlags InFlags, const TCHAR* InKey, double InValue);

	static FString GetKeyDouble(const FString& InKey, double InValue);
	static FString GetKeyDoubleC(const TCHAR* InKey, double InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32(const FString& InKey, int32 InValue);
	static void LogInt32C(const TCHAR* InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32If(bool bInShouldLog, const FString& InKey, int32 InValue);
	static void LogInt32IfC(bool bInShouldLog, const TCHAR* InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogInt32IfFlags(ELogFlags InLogFlags, const FString& InKey, int32 InValue);
	static void LogInt32IfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, int32 InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyInt32(const FString& InKey, int32 InValue);
	static FString GetKeyInt32C(const TCHAR* InKey, int32 InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogString(const FString& InKey, const FString& InValue);
	static void LogStringC(const TCHAR* InKey, const FString& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogStringIf(bool bInShouldLog, const FString& InKey, const FString& InValue);
	static void LogStringIfC(bool bInShouldLog, const TCHAR* InKey, const FString& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogStringIfFlags(ELogFlags InLogFlags, const FString& InKey, const FString& InValue);
	static void LogStringIfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, const FString& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyString(const FString& InKey, const FString& InValue);
	static FString GetKeyStringC(const TCHAR* InKey, const FString& InValue);
	
	static void LogCString(const FString& InKey, const TCHAR* InValue);
	static void LogCStringC(const TCHAR* InKey, const TCHAR* InValue);
	static void LogCStringIf(bool bInShouldLog, const FString& InKey, const TCHAR* InValue);
	static void LogCStringIfC(bool bInShouldLog, const TCHAR* InKey, const TCHAR* InValue);
	static void LogCStringIfFlags(ELogFlags InLogFlags, const FString& InKey, const TCHAR* InValue);
	static void LogCStringIfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, const TCHAR* InValue);
	static FString GetKeyCString(const FString& InKey, const TCHAR* InValue);
	static FString GetKeyCStringC(const TCHAR* InKey, const TCHAR* InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogText(const FString& InKey, const FText& InValue);
	static void LogTextC(const TCHAR* InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogTextIf(bool bInShouldLog, const FString& InKey, const FText& InValue);
	static void LogTextIfC(bool bInShouldLog, const TCHAR* InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogTextIfFlags(ELogFlags InLogFlags, const FString& InKey, const FText& InValue);
	static void LogTextIfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, const FText& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyText(const FString& InKey, const FText& InValue);
	static FString GetKeyTextC(const TCHAR* InKey, const FText& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogName(const FString& InKey, const FName& InValue);
	static void LogNameC(const TCHAR* InKey, const FName& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameIf(bool bInShouldLog, const FString& InKey, const FName& InValue);
	static void LogNameIfC(bool bInShouldLog, const TCHAR* InKey, const FName& InValue);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameIfFlags(ELogFlags InLogFlags, const FString& InKey, const FName& InValue);
	static void LogNameIfFlagsC(ELogFlags InLogFlags, const TCHAR* InKey, const FName& InValue);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyName(const FString& InKey, const FName& InValue);
	static FString GetKeyNameC(const TCHAR* InKey, const FName& InValue);
	// ~Value logging End
	
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafe(const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);
	
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafeIf(bool bInShouldLog, const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogObjectSafeIfFlags(ELogFlags InLogFlags, const UObject* InObject, EMyLogObjectFlags InFlags = EMyLogObjectFlags::Default);

	static FString GetInternalObjectFlagsString(EInternalObjectFlags InFlags);
	static FString GetInternalObjectFlagsStringScoped(EInternalObjectFlags InFlags);
	static FString GetObjectFlagsString(EObjectFlags InFlags);
	static FString GetObjectFlagsStringScoped(EObjectFlags InFlags);
};
