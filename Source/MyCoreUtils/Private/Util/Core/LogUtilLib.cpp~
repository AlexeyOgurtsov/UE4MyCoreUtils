#include "LogUtilLib.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "Math/Vector4.h"
#include "Math/Rotator.h"
#include "Math/Quat.h"
#include "Math/Plane.h"
#include "Math/Transform.h"
#include "Math/TranslationMatrix.h"
#include "Math/RotationMatrix.h"

DEFINE_LOG_CATEGORY(MyLog);

ULogUtilLib::ULogUtilLib()
{
}

FString ULogUtilLib::GetNameAndClass(const UObject* const InObject)
{
	checkf(InObject, TEXT("nullptr is invalid when using  %s, use Safe version instead"), __FUNCTION__);
	TArray<FStringFormatArg> FormatArgs;
	FormatArgs.Add(InObject->GetName());
	FormatArgs.Add(InObject->GetClass()->GetName());
	return FString::Format(TEXT("name=\"{0}\" class=\"{1}\""), FormatArgs);
}

FString ULogUtilLib::GetNameAndClassSafe(const UObject* const InObject)
{
	if(nullptr == InObject)
	{
		return FString(TEXT("nullptr"));
	}
	return GetNameAndClass(InObject);
}

FString ULogUtilLib::GetNameAndClassScoped(const UObject* const InObject)
{
	FString Result;
	Result.Append(TEXT("("));
	if(InObject)
	{
		Result.Append(GetNameAndClass(InObject));
	}
	else
	{
		Result.Append(TEXT("nullptr"));
	}
	Result.Append(TEXT(")"));
	return Result;
}

FString ULogUtilLib::GetKeyedNameAndClass(const FString& InKey, const UObject* const InObject)
{
	return GetKeyedNameAndClassC(*InKey, InObject);
}

FString ULogUtilLib::GetKeyedNameAndClassC(const TCHAR* InKey, const UObject* const InObject)
{
	return FString::Printf(TEXT("%s : %s"), InKey, *GetNameAndClassScoped(InObject)); 
}

void ULogUtilLib::LogNameClassSafe(const UObject* const InObject)
{
	M_LOG(TEXT("%s"), *GetNameAndClassSafe(InObject));
}

void ULogUtilLib::LogKeyedNameClassSafe(const FString& InKey, const UObject* const InObject)
{
	LogKeyedNameClassSafeC(*InKey, InObject);
}

void ULogUtilLib::LogKeyedNameClassSafeC(const TCHAR* InKey, const UObject* const InObject)
{
	M_LOG(TEXT("%s"), *GetKeyedNameAndClassC(InKey, InObject));
}

void ULogUtilLib::LogKeyedNameClassSafeIf(bool const bInShouldLog, const FString& InKey, const UObject* const InObject)
{
	LogKeyedNameClassSafeIfC(bInShouldLog, *InKey, InObject);
}

void ULogUtilLib::LogKeyedNameClassSafeIfC(bool const bInShouldLog, const TCHAR* const InKey, const UObject* const InObject)
{
	if(bInShouldLog)
	{
		LogKeyedNameClassSafeC(InKey, InObject);
	}
}

void ULogUtilLib::LogVector(const FString& InKey, const FVector& InVector)
{
	LogVectorC(*InKey, InVector);
}

void ULogUtilLib::LogVectorC(const TCHAR* InKey, const FVector& InVector)
{
	LogStringC(InKey, InVector.ToString());
}

void ULogUtilLib::LogVectorIf(bool bInShouldLog, const FString& InKey, const FVector& InVector)
{
	LogVectorIfC(bInShouldLog, *InKey, InVector);
}

void ULogUtilLib::LogVectorIfC(bool bInShouldLog, const TCHAR* InKey, const FVector& InVector)
{
	if(bInShouldLog)
	{
		LogVectorC(InKey, InVector);
	}
}

void ULogUtilLib::LogVector2DC(const TCHAR* InKey, const FVector2D& InVector)
{
	LogStringC(InKey, InVector.ToString());
}

void ULogUtilLib::LogVector2D(const FString& InKey, const FVector2D& InVector)
{
	LogVector2DC(*InKey, InVector);
}


void ULogUtilLib::LogVector2DIf(bool bInShouldLog, const FString& InKey, const FVector2D& InVector)
{
	LogVector2DIfC(bInShouldLog, *InKey, InVector);
}

void ULogUtilLib::LogVector2DIfC(bool bInShouldLog, const TCHAR* InKey, const FVector2D& InVector)
{
	if(bInShouldLog)
	{
		LogVector2DC(InKey, InVector);
	}
}

void ULogUtilLib::LogVector4(const FString& InKey, const FVector4& InVector)
{
	LogVector4C(*InKey, InVector);
}

void ULogUtilLib::LogVector4C(const TCHAR* InKey, const FVector4& InVector)
{
	LogStringC(InKey, InVector.ToString());
}

void ULogUtilLib::LogVector4If(bool bInShouldLog, const FString& InKey, const FVector4& InVector)
{
	LogVector4IfC(bInShouldLog, *InKey, InVector);
}

void ULogUtilLib::LogVector4IfC(bool bInShouldLog, const TCHAR* InKey, const FVector4& InVector)
{
	if(bInShouldLog)
	{
		return;
	}
}

void ULogUtilLib::LogRotator(const FString& InKey, const FRotator& InRotator)
{
	LogRotatorC(*InKey, InRotator);
}

void ULogUtilLib::LogRotatorC(const TCHAR* InKey, const FRotator& InRotator)
{
	LogStringC(InKey, InRotator.ToString());
}

void ULogUtilLib::LogRotatorIf(bool bInShouldLog, const FString& InKey, const FRotator& InRotator)
{
	LogRotatorIfC(bInShouldLog, *InKey, InRotator);
}

void ULogUtilLib::LogRotatorIfC(bool bInShouldLog, const TCHAR* InKey, const FRotator& InRotator)
{
	if(bInShouldLog)
	{
		LogRotatorC(InKey, InRotator);
	}
}

void ULogUtilLib::LogQuat(const FString& InKey, const FQuat& InQuat)
{
	LogQuatC(*InKey, InQuat);
}

void ULogUtilLib::LogQuatC(const TCHAR* InKey, const FQuat& InQuat)
{
	FVector Axis;
	float Angle;
	InQuat.ToAxisAndAngle(Axis, Angle);

	TArray<FStringFormatArg> const FormatArgs
	{
		InQuat.ToString(),
		Axis.ToString(),
		Angle,
		InQuat.Rotator().ToString()
	};

	LogStringC(InKey, FString::Format(TEXT("{0} [Axis={1} Angle={2}] { {3} }"), FormatArgs));
}

void ULogUtilLib::LogQuatIf(bool bInShouldLog, const FString& InKey, const FQuat& InQuat)
{
	LogQuatIfC(bInShouldLog, *InKey, InQuat);
}

void ULogUtilLib::LogQuatIfC(bool bInShouldLog, const TCHAR* InKey, const FQuat& InQuat)
{
	if(bInShouldLog)
	{
		LogQuatC(InKey, InQuat);
	}
}

void ULogUtilLib::LogTransform(const FString& InKey, const FTransform& InTransform)
{
	LogTransformC(*InKey, InTransform);
}

void ULogUtilLib::LogTransformC(const TCHAR* InKey, const FTransform& InTransform)
{
	LogVectorC(*FString::Printf(TEXT("%s.Translation"), InKey), InTransform.GetTranslation());
	LogQuatC(*FString::Printf(TEXT("%s.Rotation"), InKey), InTransform.GetRotation());
	LogVectorC(*FString::Printf(TEXT("%s.Scale3D"), InKey), InTransform.GetScale3D());
}

void ULogUtilLib::LogTransformIf(bool bInShouldLog, const FString& InKey, const FTransform& InTransform)
{
	LogTransformIfC(bInShouldLog, *InKey, InTransform);
}

void ULogUtilLib::LogTransformIfC(bool bInShouldLog, const TCHAR* InKey, const FTransform& InTransform)
{
	if(bInShouldLog)
	{
		LogTransformC(InKey, InTransform);
	}
}

void ULogUtilLib::LogPlane(const FString& InKey, const FPlane& InPlane)
{
	LogPlaneC(*InKey, InPlane);
}

void ULogUtilLib::LogPlaneC(const TCHAR* InKey, const FPlane& InPlane)
{
	LogStringC(InKey, InPlane.ToString());
}

void ULogUtilLib::LogPlaneIf(bool bInShouldLog, const FString& InKey, const FPlane& InPlane)
{
	LogPlaneIfC(bInShouldLog, *InKey, InPlane);
}

void ULogUtilLib::LogPlaneIfC(bool bInShouldLog, const TCHAR* InKey, const FPlane& InPlane)
{
	if(bInShouldLog)
	{
		LogPlaneC(InKey, InPlane);
	}
}

FString ULogUtilLib::GetYesNo(bool const bYes)
{
	return bYes ? FString(TEXT("YES")) : FString(TEXT("no"));
}

FString ULogUtilLib::GetKeyYesNo(const FString& InKey, bool const bInValue)
{
	return GetKeyYesNoC(*InKey, bInValue);
}

FString ULogUtilLib::GetKeyYesNoC(const TCHAR* const InKey, bool const bInValue)
{
	return FString::Printf(TEXT("%s : %s"), InKey, *GetYesNo(bInValue));
}

void ULogUtilLib::LogYesNo(const FString& InKey, bool const bInValue)
{
	return LogYesNoC(*InKey, bInValue);
}

void ULogUtilLib::LogYesNoC(const TCHAR* const InKey, bool const bInValue)
{
	M_LOG(TEXT("%s : %s"), InKey, *GetYesNo(bInValue));
}

void ULogUtilLib::LogYesNoIf(bool const bInShouldLog, const FString& InKey, bool const bInValue)
{
	return LogYesNoIfC(bInShouldLog, *InKey, bInValue);
}

void ULogUtilLib::LogYesNoIfC(bool const bInShouldLog, const TCHAR* const InKey, bool const bInValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : %s"), InKey, *GetYesNo(bInValue));
}

void ULogUtilLib::LogYesNoIfFlags(ELogFlags const InLogFlags, const FString& InKey, bool const bInValue)
{
	return LogYesNoIfFlagsC(InLogFlags, *InKey, bInValue);
}

void ULogUtilLib::LogYesNoIfFlagsC(ELogFlags const InLogFlags, const TCHAR* const InKey, bool const bInValue)
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%s : %s"), InKey, *GetYesNo(bInValue));
}

void ULogUtilLib::LogFloat(const FString& InKey, float const InValue)
{
	LogFloatC(*InKey, InValue);
}

void ULogUtilLib::LogFloatC(const TCHAR* const InKey, float const InValue)
{
	M_LOG(TEXT("%s : %f"), InKey, InValue);
}

void ULogUtilLib::LogFloatIfC(bool const bInShouldLog, const TCHAR* const InKey, float const InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : %f"), InKey, InValue);
}

void ULogUtilLib::LogFloatIf(bool const bInShouldLog, const FString& InKey, float const InValue)
{
	LogFloatIfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogFloatIfFlagsC(ELogFlags const InFlags, const TCHAR* const InKey, float const InValue)
{
	M_LOG_IF_FLAGS(InFlags, TEXT("%s : %f"), InKey, InValue);
}

void ULogUtilLib::LogFloatIfFlags(ELogFlags const InFlags, const FString& InKey, float const InValue)
{
	LogFloatIfFlagsC(InFlags, *InKey, InValue);
}

FString ULogUtilLib::GetKeyFloat(const FString& InKey, float const InValue)
{
	return GetKeyFloatC(*InKey, InValue);
}

FString ULogUtilLib::GetKeyFloatC(const TCHAR* const InKey, float const InValue)
{
	return FString::Printf(TEXT("%s : %f"), InKey, InValue);
}
void ULogUtilLib::LogDouble(const FString& InKey, double const InValue)
{
	LogDoubleC(*InKey, InValue);
}

void ULogUtilLib::LogDoubleC(const TCHAR* const InKey, double const InValue)
{
	M_LOG(TEXT("%s : %lf"), InKey, InValue);
}

void ULogUtilLib::LogDoubleIf(bool const bInShouldLog, const FString& InKey, double const InValue)
{
	LogDoubleIfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogDoubleIfC(bool const bInShouldLog, const TCHAR* const InKey, double const InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : %lf"), InKey, InValue);
}

void ULogUtilLib::LogDoubleIfFlags(ELogFlags const InFlags, const FString& InKey, double const InValue)
{
	LogDoubleIfFlagsC(InFlags, *InKey, InValue);
}

void ULogUtilLib::LogDoubleIfFlagsC(ELogFlags const InFlags, const TCHAR* const InKey, double const InValue)
{
	M_LOG_IF_FLAGS(InFlags, TEXT("%s : %lf"), InKey, InValue);
}

FString ULogUtilLib::GetKeyDouble(const FString& InKey, double const InValue)
{
	return GetKeyDoubleC(*InKey, InValue);
}

FString ULogUtilLib::GetKeyDoubleC(const TCHAR* const InKey, double const InValue)
{
	return FString::Printf(TEXT("%s : %lf"), InKey, InValue);
}

void ULogUtilLib::LogInt32(const FString& InKey, int32 const InValue)
{
	LogInt32C(*InKey, InValue);
}

void ULogUtilLib::LogInt32C(const TCHAR* const InKey, int32 const InValue)
{
	M_LOG(TEXT("%s : %d"), InKey, InValue);
}

void ULogUtilLib::LogInt32If(bool const bInShouldLog, const FString& InKey, int32 const InValue)
{
	LogInt32IfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogInt32IfC(bool const bInShouldLog, const TCHAR* InKey, int32 const InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : %d"), InKey, InValue);
}

void ULogUtilLib::LogInt32IfFlags(ELogFlags const InLogFlags, const FString& InKey, int32 const InValue)
{
	LogInt32IfFlagsC(InLogFlags, *InKey, InValue);
}

void ULogUtilLib::LogInt32IfFlagsC(ELogFlags const InLogFlags, const TCHAR* const InKey, int32 const InValue)
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%s : %d"), InKey, InValue);
}

FString ULogUtilLib::GetKeyInt32(const FString& InKey, int32 InValue)
{
	return GetKeyInt32C(*InKey, InValue);
}

FString ULogUtilLib::GetKeyInt32C(const TCHAR* const InKey, int32 InValue)
{
	return FString::Printf(TEXT("%s : %d"), InKey, InValue);
}

void ULogUtilLib::LogString(const FString& InKey, const FString& InValue)
{
	LogCString(InKey, *InValue);
}
void ULogUtilLib::LogStringC(const TCHAR* const InKey, const FString& InValue)
{
	LogCStringC(InKey, *InValue);
}
void ULogUtilLib::LogStringIf(bool const bInShouldLog, const FString& InKey, const FString& InValue)
{
	LogCStringIf(bInShouldLog, InKey, *InValue);
}

void ULogUtilLib::LogStringIfC(bool const bInShouldLog, const TCHAR* const InKey, const FString& InValue)
{
	LogCStringIfC(bInShouldLog, InKey, *InValue);
}
void ULogUtilLib::LogStringIfFlags(ELogFlags const InLogFlags, const FString& InKey, const FString& InValue)
{
	LogCStringIfFlags(InLogFlags, InKey, *InValue);
}

void ULogUtilLib::LogStringIfFlagsC(ELogFlags const InLogFlags, const TCHAR* const InKey, const FString& InValue)
{
	LogCStringIfFlagsC(InLogFlags, InKey, *InValue);
}
void ULogUtilLib::LogCString(const FString& InKey, const TCHAR* InValue)
{
	LogCStringC(*InKey, InValue);
}

void ULogUtilLib::LogCStringC(const TCHAR* const InKey, const TCHAR* InValue)
{
	M_LOG(TEXT("%s : \"%s\""), InKey, InValue);

}
void ULogUtilLib::LogCStringIf(bool bInShouldLog, const FString& InKey, const TCHAR* const InValue)
{
	LogCStringIfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogCStringIfC(bool bInShouldLog, const TCHAR* const InKey, const TCHAR* const InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : \"%s\""), InKey, InValue);
}
void ULogUtilLib::LogCStringIfFlags(ELogFlags InLogFlags, const FString& InKey, const TCHAR* const InValue)
{
	LogCStringIfFlagsC(InLogFlags, *InKey, InValue);
}

void ULogUtilLib::LogCStringIfFlagsC(ELogFlags InLogFlags, const TCHAR* const InKey, const TCHAR* const InValue)
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%s : \"%s\""), InKey, InValue);
}

FString ULogUtilLib::GetKeyCString(const FString& InKey, const TCHAR* const InValue)
{
	return GetKeyCStringC(*InKey, InValue);
}

FString ULogUtilLib::GetKeyCStringC(const TCHAR* const InKey, const TCHAR* const InValue)
{
	return FString::Printf(TEXT("%s : \"%s\""), InKey, InValue);
}
FString ULogUtilLib::GetKeyString(const FString& InKey, const FString& InValue)
{
	return GetKeyCString(InKey, *InValue);
}

FString ULogUtilLib::GetKeyStringC(const TCHAR* const InKey, const FString& InValue)
{
	return GetKeyCStringC(InKey, *InValue);
}

void ULogUtilLib::LogText(const FString& InKey, const FText& InValue)
{
	LogTextC(*InKey, InValue);
}

void ULogUtilLib::LogTextC(const TCHAR* const InKey, const FText& InValue)
{
	M_LOG(TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogTextIf(bool const bInShouldLog, const FString& InKey, const FText& InValue)
{
	LogTextIfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogTextIfC(bool const bInShouldLog, const TCHAR* const InKey, const FText& InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogTextIfFlags(ELogFlags const InLogFlags, const FString& InKey, const FText& InValue)
{
	LogTextIfFlagsC(InLogFlags, *InKey, InValue);
}
 
void ULogUtilLib::LogTextIfFlagsC(ELogFlags const InLogFlags, const TCHAR* const InKey, const FText& InValue)
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

FString ULogUtilLib::GetKeyText(const FString& InKey, const FText& InValue)
{
	return GetKeyTextC(*InKey, InValue);
}

FString ULogUtilLib::GetKeyTextC(const TCHAR* const InKey, const FText& InValue)
{
	return FString::Printf(TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogName(const FString& InKey, const FName& InValue)
{
	LogNameC(*InKey, InValue);
}

void ULogUtilLib::LogNameC(const TCHAR* const InKey, const FName& InValue)
{
	M_LOG(TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogNameIf(bool const bInShouldLog, const FString& InKey, const FName& InValue)
{
	LogNameIfC(bInShouldLog, *InKey, InValue);
}

void ULogUtilLib::LogNameIfC(bool const bInShouldLog, const TCHAR* const InKey, const FName& InValue)
{
	M_LOG_IF(bInShouldLog, TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogNameIfFlags(ELogFlags const InLogFlags, const FString& InKey, const FName& InValue)
{
	LogNameIfFlagsC(InLogFlags, *InKey, InValue);
}

void ULogUtilLib::LogNameIfFlagsC(ELogFlags const InLogFlags, const TCHAR* const InKey, const FName& InValue)
{
	M_LOG_IF_FLAGS(InLogFlags, TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

FString ULogUtilLib::GetKeyName(const FString& InKey, const FName& InValue)
{
	return GetKeyNameC(*InKey, InValue);
}

FString ULogUtilLib::GetKeyNameC(const TCHAR* const InKey, const FName& InValue)
{
	return FString::Printf(TEXT("%s : \"%s\""), InKey, *InValue.ToString());
}

void ULogUtilLib::LogObjectSafe(const UObject* const InObject, EMyLogObjectFlags const InFlags)
{
	return LogObjectSafeIf(true, InObject, InFlags);
}

void ULogUtilLib::LogObjectSafeIf(bool const bInShouldLog, const UObject* const InObject, EMyLogObjectFlags const InFlags)
{
	if(bInShouldLog == false)
	{
		return;
	}

	M_LOGFUNC();
	M_LOG(TEXT("Logging object {%s}"), *GetNameAndClassSafe(InObject));
	// GetFullName DO safe to call on nullptr pointers:
	if( (InFlags & EMyLogObjectFlags::SuppressNameAndClass) == EMyLogObjectFlags::None )
	{
		M_LOG(TEXT("FullName: {%s}"), *InObject->GetFullName());
	}
	if(InObject)
	{
		if(false == InObject->IsValidLowLevelFast(false))
		{
			M_LOG_ERROR(TEXT("Object is invalid Low-level NON_RECURSIVE (IsValidLowLevelFast(false) returned false)"));
		}
		if(false == InObject->IsValidLowLevelFast(true))
		{
			M_LOG_ERROR(TEXT("Object is invalid Low-level RECURSIVE (IsValidLowLevelFast(true) returned false)"));
		}
		if( (InFlags & EMyLogObjectFlags::FullGroupName) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("FullGroupName: {%s}"), *InObject->GetFullGroupName(/*bStartWithOuter*/true));
		}
		if( (InFlags & EMyLogObjectFlags::Outer) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Outer: {%s}"), *GetNameAndClassSafe(InObject->GetOuter()));
		}
		if( (InFlags & EMyLogObjectFlags::ObjectFlags) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Flags: %s"), *GetObjectFlagsStringScoped(InObject->GetFlags()));
		}
		if( (InFlags & EMyLogObjectFlags::InternalObjectFlags) != EMyLogObjectFlags::None )
		{
			M_LOG(TEXT("Internal Flags: %s"), *GetInternalObjectFlagsStringScoped(InObject->GetInternalFlags()));
		}
	}

}	
void ULogUtilLib::LogObjectSafeIfFlags(ELogFlags InLogFlags, const UObject* InObject, EMyLogObjectFlags InFlags)
{
	bool const bShouldLog = UMyLoggingTypes::ShouldLogVerbosity(InLogFlags, ELogVerbosity::Type::Log);
	LogObjectSafeIf(bShouldLog, InObject, InFlags);
}

FString ULogUtilLib::GetInternalObjectFlagsStringScoped(EInternalObjectFlags const InFlags)
{
	return FString::Printf(TEXT("{%s}"), *GetInternalObjectFlagsString(InFlags));
}

FString ULogUtilLib::GetInternalObjectFlagsString(EInternalObjectFlags const InFlags)
{
	FString S;
	if(InFlags == EInternalObjectFlags::None)
	{
		return FString(TEXT("None"));
	}
	else
	{
		if((InFlags & EInternalObjectFlags::ReachableInCluster) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("ReachableInCluster | "));
		}
		if((InFlags & EInternalObjectFlags::ClusterRoot)  != EInternalObjectFlags::None)
		{
			S.Append(TEXT("ClusterRoot | "));
		}
		if((InFlags & EInternalObjectFlags::Native) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Native | "));
		}
		if((InFlags & EInternalObjectFlags::Async) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Async | "));
		}
		if((InFlags & EInternalObjectFlags::AsyncLoading) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("AsyncLoading | "));
		}
		if((InFlags & EInternalObjectFlags::Unreachable) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("Unreachable | "));
		}
		if((InFlags & EInternalObjectFlags::PendingKill) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("PendingKill | "));
		}
		if((InFlags & EInternalObjectFlags::RootSet) != EInternalObjectFlags::None)
		{
			S.Append(TEXT("RootSet | "));
		}
	}
	return S;
}

FString ULogUtilLib::GetObjectFlagsStringScoped(EObjectFlags const InFlags)
{
	return FString::Printf(TEXT("{%s}"), *GetObjectFlagsString(InFlags));
}

FString ULogUtilLib::GetObjectFlagsString(EObjectFlags const InFlags)
{
	FString S;
	if(InFlags == EObjectFlags::RF_NoFlags)
	{
		return FString(TEXT("None"));
	}
	else
	{
		if((InFlags & EObjectFlags::RF_Public) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Public | "));
		}
		if((InFlags & EObjectFlags::RF_Standalone) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Standalone | "));
		}
		if((InFlags & EObjectFlags::RF_MarkAsNative) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("MarkAsNative | "));
		}
		if((InFlags & EObjectFlags::RF_Transactional) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Transactional | "));
		}
		if((InFlags & EObjectFlags::RF_ClassDefaultObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("ClassDefaultObject | "));
		}
		if((InFlags & EObjectFlags::RF_ArchetypeObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("ArchetypeObject | "));
		}
		if((InFlags & EObjectFlags::RF_Transient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Transient | "));
		}
		if((InFlags & EObjectFlags::RF_MarkAsRootSet) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("MarkAsRootSet | "));
		}
		if((InFlags & EObjectFlags::RF_TagGarbageTemp) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("TagGarbageTemp | "));
		}
		if((InFlags & EObjectFlags::RF_NeedInitialization) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedInitialization | "));
		}
		if((InFlags & EObjectFlags::RF_NeedLoad) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedLoad | "));
		}
		if((InFlags & EObjectFlags::RF_KeepForCooker) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("KeepForCooker | "));
		}
		if((InFlags & EObjectFlags::RF_NeedPostLoad) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedPostLoad | "));
		}
		if((InFlags & EObjectFlags::RF_NeedPostLoadSubobjects) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NeedPostLoadSubobjects | "));
		}
		if((InFlags & EObjectFlags::RF_NewerVersionExists) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NewerVersionExists | "));
		}
		if((InFlags & EObjectFlags::RF_BeginDestroyed) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("BeginDestroyed | "));
		}
		if((InFlags & EObjectFlags::RF_FinishDestroyed) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("FinishDestroyed | "));
		}
		if((InFlags & EObjectFlags::RF_BeingRegenerated) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("BeingRegenerated | "));
		}
		if((InFlags & EObjectFlags::RF_DefaultSubObject) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("DefaultSubObject | "));
		}
		if((InFlags & EObjectFlags::RF_WasLoaded) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("WasLoaded | "));
		}
		if((InFlags & EObjectFlags::RF_TextExportTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("TextExportTransient | "));
		}
		if((InFlags & EObjectFlags::RF_LoadCompleted) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("LoadCompleted | "));
		}
		if((InFlags & EObjectFlags::RF_InheritableComponentTemplate) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("InheritableComponentTemplate | "));
		}
		if((InFlags & EObjectFlags::RF_DuplicateTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("DuplicateTransient | "));
		}
		if((InFlags & EObjectFlags::RF_StrongRefOnFrame) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("StrongRefOnFrame | "));
		}
		if((InFlags & EObjectFlags::RF_NonPIEDuplicateTransient) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("NonPIEDuplicateTransient | "));
		}
		if((InFlags & EObjectFlags::RF_Dynamic) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("Dynamic | "));
		}
		if((InFlags & EObjectFlags::RF_WillBeLoaded) != EObjectFlags::RF_NoFlags)
		{
			S.Append(TEXT("WillBeLoaded | "));
		}
		return S;
	}
}
