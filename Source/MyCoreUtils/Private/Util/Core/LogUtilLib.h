#pragma once

#include "MyDebugMacros.h"
#include "Log/MyLoggingTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UObject\TextProperty.h"
#include "GenericPlatform/GenericPlatformMisc.h"
#include "LogUtilLib.generated.h"

/**
* @TODO Array utils:
* 1. Should take UObject-derived classes also!
*/

inline const TCHAR* StringDeref(const FString& S) 
{
       	return *S;
}

inline const TCHAR* TextStringDeref(const FText& S) 
{
       	return *S.ToString();
}

inline const TCHAR* NameStringDeref(const FName& S) 
{
       	return *S.ToString();
}

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
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

UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsFlagValuesInEditor="true"))
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

	/**
	* Log number of elements
	*/
	LogCount                   = 1 << 4       UMETA(DisplayName="Log Count"),

	Default                    = LogSummary | LogIndex            UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ELogRangeFlags);

struct FVector;
struct FVector2D;
struct FVector4;
struct FQuat;
struct FRotator;
struct FTransform;
struct FPlane;

class FTranslationMatrix;
class FRotationMatrix;

UCLASS()
class ULogUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	ULogUtilLib();

	/**
	* Returns name and class of the object.
	* @note: nullptr object is invalid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClass(const UObject* InObject);

	/**
	* Returns name and class of the object.
	* @note: nullptr object is valid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassSafe(const UObject* InObject);

	/**
	* Returns name and class of the object pointed to by the given weak object ptr.
	* @note: nullptr object is valid.
	*/
	template<class T>
	static FString GetWeakNameAndClassSafe(const TWeakObjectPtr<T>& InObject, bool bInThreadSafe = false)
	{
		if( ! InObject.IsValid(/*bEverIfPendingKill*/true, bInThreadSafe) )
		{
			return FString(TEXT("{invalid_weak_ptr}"));
		}

		T* const Obj = InObject.GetEvenIfUnreachable();
		checkf(Obj, TEXT("Returned object ptr for weak object must be valid (because we already tested it earlier in the function)"));

		FString const FlagsString = GetObjectFlagsString(Obj->GetFlags());
		return FString::Printf(TEXT("%s [%s]"), *GetNameAndClassSafe(Obj), *FlagsString);
	}

	/**
	* Returns name and class of the object, enclosed in brackets.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassScoped(const UObject* InObject);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetKeyedNameAndClass(const FString& InKey, const UObject* InObject);
	static FString GetKeyedNameAndClassC(const TCHAR* InKey, const UObject* InObject);

	// ~Container logging Begin
	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogStringArray"))
	static void K2LogStringArray(const TArray<FString>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogTextArray"))
	static void K2LogTextArray(const TArray<FText>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogNameArray"))
	static void K2LogNameArray(const TArray<FName>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogStringSet"))
	static void K2LogStringSet(const TSet<FString>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log, Meta=(DisplayName="LogNameSet"))
	static void K2LogNameSet(const TSet<FName>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	UFUNCTION(BlueprintCallable, Category = Log, Meta = (DisplayName = "LogStringMap"))
	static void K2LogStringMap(const TMap<FString, FString>& InContainer, ELogRangeFlags Flags = ELogRangeFlags::Default);

	template<class T>
	static void LogArray(const TArray<T>& Array, TFunction<const TCHAR*(const T&)> ToStringFunc, ELogRangeFlags Flags = ELogRangeFlags::Default)	
	{
		int32 Index = 0;
		for(const T& Elem : Array)
		{
			M_LOG(TEXT("%s"), ToStringFunc(Elem));
			Index++;
		}
	}

	template<class T>
	static void LogSet(const TSet<T>& Cont, TFunction<const TCHAR*(const T&)> ToStringFunc, ELogRangeFlags Flags = ELogRangeFlags::Default)	
	{
		int32 Index = 0;
		for(TSet<T>::TConstIterator Itr = Cont.CreateConstIterator(); Itr; ++Itr)
		{
			M_LOG(TEXT("%s"), ToStringFunc(*Itr));
			Index++;
		}
	}

	template<class K, class V>
	static void LogMap
	(
		const TMap<K, V>& Cont, 
		TFunction<const TCHAR*(const K&)> KeyToStringFunc, 
		TFunction<const TCHAR*(const V&)> ValToStringFunc, 
		ELogRangeFlags Flags = ELogRangeFlags::Default
	)	
	{
		int32 Index = 0;
		for(TMap<K, V>::TConstIterator Itr = Cont.CreateConstIterator(); Itr; ++Itr)
		{
			M_LOG(TEXT("[\"%s\"]: \"%s\""), KeyToStringFunc(Itr.Key()), ValToStringFunc(Itr.Value()));
			Index++;
		}
	}
	// ~Container logging End

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
	
	// ~Math value logging Begin
	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVector(const FString& InKey, const FVector& InVector);
	static void LogVectorC(const TCHAR* InKey, const FVector& InVector);
	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVectorIf(bool bInShouldLog, const FString& InKey, const FVector& InVector);
	static void LogVectorIfC(bool bInShouldLog, const TCHAR* InKey, const FVector& InVector);

	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVector2D(const FString& InKey, const FVector2D& InVector);
	static void LogVector2DC(const TCHAR* InKey, const FVector2D& InVector);
	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVector2DIf(bool bInShouldLog, const FString& InKey, const FVector2D& InVector);
	static void LogVector2DIfC(bool bInShouldLog, const TCHAR* InKey, const FVector2D& InVector);

	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVector4(const FString& InKey, const FVector4& InVector);
	static void LogVector4C(const TCHAR* InKey, const FVector4& InVector);
	UFUNCTION(BlueprintCallable, Category = "Log|Transform|Math")
	static void LogVector4If(bool bInShouldLog, const FString& InKey, const FVector4& InVector);
	static void LogVector4IfC(bool bInShouldLog, const TCHAR* InKey, const FVector4& InVector);

	UFUNCTION(BlueprintCallable, Category = "Log|Math|Transform|Rotation")
	static void LogRotator(const FString& InKey, const FRotator& InRotator);
	static void LogRotatorC(const TCHAR* InKey, const FRotator& InRotator);
	UFUNCTION(BlueprintCallable, Category = "Log|Math|Transform|Rotation")
	static void LogRotatorIf(bool bInShouldLog, const FString& InKey, const FRotator& InRotator);
	static void LogRotatorIfC(bool bInShouldLog, const TCHAR* InKey, const FRotator& InRotator);

	static void LogQuat(const FString& InKey, const FQuat& InQuat);
	static void LogQuatC(const TCHAR* InKey, const FQuat& InQuat);
	static void LogQuatIf(bool bInShouldLog, const FString& InKey, const FQuat& InQuat);
	static void LogQuatIfC(bool bInShouldLog, const TCHAR* InKey, const FQuat& InQuat);

	UFUNCTION(BlueprintCallable, Category = "Log|Math|Transform")
	static void LogTransform(const FString& InKey, const FTransform& InTransform);
	static void LogTransformC(const TCHAR* InKey, const FTransform& InTransform);
	UFUNCTION(BlueprintCallable, Category = "Log|Math|Transform")
	static void LogTransformIf(bool bInShouldLog, const FString& InKey, const FTransform& InTransform);
	static void LogTransformIfC(bool bInShouldLog, const TCHAR* InKey, const FTransform& InTransform);

	UFUNCTION(BlueprintCallable, Category = "Log|Math|Transform")
	static void LogPlane(const FString& InKey, const FPlane& InPlane);
	static void LogPlaneC(const TCHAR* InKey, const FPlane& InPlane);
	UFUNCTION(BlueprintCallable, Category = "Log|Math|Plane")
	static void LogPlaneIf(bool bInShouldLog, const FString& InKey, const FPlane& InPlane);
	static void LogPlaneIfC(bool bInShouldLog, const TCHAR* InKey, const FPlane& InPlane);

	static void LogTranslationMatrix(const FString& InKey, const FTranslationMatrix& InMatrix);
	static void LogTranslationMatrixC(const TCHAR* InKey, const FTranslationMatrix& InMatrix);
	static void LogTranslationMatrixIf(bool bInShouldLog, const FString& InKey, const FTranslationMatrix& InMatrix);
	static void LogTranslationMatrixIfC(bool bInShouldLog, const TCHAR* InKey, const FTranslationMatrix& InMatrix);

	static void LogRotationMatrix(const FString& InKey, const FRotationMatrix& InMatrix);
	static void LogRotationMatrixC(const TCHAR* InKey, const FRotationMatrix& InMatrix);
	static void LogRotationMatrixIf(bool bInShouldLog, const FString& InKey, const FRotationMatrix& InMatrix);
	static void LogRotationMatrixIfC(bool bInShouldLog, const TCHAR* InKey, const FRotationMatrix& InMatrix);
	// ~Math value logging End

	// ~Value logging Begin
	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogNameClassSafe(const UObject* InObject);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogKeyedNameClassSafe(const FString& InKey, const UObject* InObject);
	static void LogKeyedNameClassSafeC(const TCHAR* InKey, const UObject* InObject);

	UFUNCTION(BlueprintCallable, Category = Log)
	static void LogKeyedNameClassSafeIf(bool bInShouldLog, const FString& InKey, const UObject* InObject); 
	static void LogKeyedNameClassSafeIfC(bool bInShouldLog, const TCHAR* InKey, const UObject* InObject);

	template<class T>
	static void LogWeakKeyedNameClassSafe(const FString& InKey, const TWeakObjectPtr<T>& InObject, bool bInThreadSafe = false)
	{
		LogWeakKeyedNameClassSafeC(*InKey, InObject, bInThreadSafe);
	}

	template<class T>
	static void LogWeakKeyedNameClassSafeC(const TCHAR* InKey, const TWeakObjectPtr<T>& InObject, bool bInThreadSafe = false)
	{
		M_LOG(TEXT("%s: %s"), InKey, *GetWeakNameAndClassSafe(InObject, bInThreadSafe));
	}

	template<class T>
	static void LogWeakKeyedNameClassSafeIf(bool bInShouldLog, const FString& InKey, const TWeakObjectPtr<T>& InObject, bool bInThreadSafe = false)
	{
		LogWeakKeyedNameClassSafeIfC(bInShouldLog, *InKey, InObject, bInThreadSafe);
	}

	template<class T>
	static void LogWeakKeyedNameClassSafeIfC(bool bInShouldLog, const TCHAR* InKey, const TWeakObjectPtr<T>& InObject, bool bInThreadSafe = false)
	{
		if(bInShouldLog)
		{
			LogWeakKeyedNameClassSafeC(InKey, InObject, bInThreadSafe);
		}
	}

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
