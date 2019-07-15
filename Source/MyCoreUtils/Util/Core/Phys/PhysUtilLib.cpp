#include "PhysUtilLib.h"
#include "GameFramework/Actor.h" // For casts
#include "Components/PrimitiveComponent.h" // For casts
#include "PhysicalMaterials/PhysicalMaterial.h" // For casts
#include "WorldCollision.h"
#include "Util/Core/TypeUtilLib.h"
#include "Util/Core/LogUtilLib.h"


void UPhysUtilLib::LogHitResult(const FHitResult& InHitResult, ELogHitFlags const InFlags)
{
	M_LOGFUNC();

	const bool bExtOwner = ((InFlags & ELogHitFlags::LeanAndMeanOwner) == ELogHitFlags::None);
	const bool bExtLocation = ((InFlags & ELogHitFlags::LeanAndMeanLocation) == ELogHitFlags::None);

	ULogUtilLib::LogYesNoC(TEXT("bBlockingHit"), InHitResult.bBlockingHit);

	ULogUtilLib::LogYesNoC(TEXT("bStartPenetrating"), InHitResult.bStartPenetrating);
	ULogUtilLib::LogInt32C(TEXT("FaceIndex"), InHitResult.FaceIndex);

	ULogUtilLib::LogFloatC(TEXT("Time (0.0F to 1.0F)"), InHitResult.Time);
	ULogUtilLib::LogFloatC(TEXT("Distance"), InHitResult.Distance);

	ULogUtilLib::LogStringC(TEXT("Location"), InHitResult.Location.ToString());
	ULogUtilLib::LogStringC(TEXT("ImpactPoint"), InHitResult.ImpactPoint.ToString());
	ULogUtilLib::LogStringC(TEXT("Normal"), InHitResult.Normal.ToString());

	ULogUtilLib::LogStringC(TEXT("ImpactNormal"), InHitResult.ImpactNormal.ToString());

	ULogUtilLib::LogStringC(TEXT("TraceStart"), InHitResult.TraceStart.ToString());
	ULogUtilLib::LogStringC(TEXT("TraceEnd"), InHitResult.TraceEnd.ToString());

	ULogUtilLib::LogFloatC(TEXT("PenetrationDepth"), InHitResult.PenetrationDepth);

	ULogUtilLib::LogInt32C(TEXT("Item"), InHitResult.Item);

	ULogUtilLib::LogWeakKeyedNameClassSafeIfC(bExtOwner, TEXT("PhysMaterial"), InHitResult.PhysMaterial);
	ULogUtilLib::LogWeakKeyedNameClassSafeC(TEXT("Actor"), InHitResult.Actor);
	ULogUtilLib::LogWeakKeyedNameClassSafeC(TEXT("Component"), InHitResult.Component);

	ULogUtilLib::LogNameIfC(bExtLocation, TEXT("BoneName"), InHitResult.BoneName);
	ULogUtilLib::LogNameIfC(bExtLocation, TEXT("MyBoneName"), InHitResult.MyBoneName);
}

void UPhysUtilLib::LogHitResultIf(bool const bInShouldLog, const FHitResult& InHitResult, ELogHitFlags const InFlags)
{
	if(bInShouldLog)
	{
		LogHitResult(InHitResult, InFlags);
	}
}
void UPhysUtilLib::LogCollisionQueryParams(const FCollisionQueryParams& InParams)
{
	ULogUtilLib::LogYesNoC(TEXT("bFindInitialOverlaps"), InParams.bFindInitialOverlaps);
	ULogUtilLib::LogYesNoC(TEXT("bIgnoreBlocks"), InParams.bIgnoreBlocks);
	ULogUtilLib::LogYesNoC(TEXT("bIgnoreTouches"), InParams.bIgnoreTouches);
	ULogUtilLib::LogYesNoC(TEXT("bReturnFaceIndex"), InParams.bReturnFaceIndex);
	ULogUtilLib::LogYesNoC(TEXT("bReturnPhysicalMaterial"), InParams.bReturnPhysicalMaterial);
	ULogUtilLib::LogYesNoC(TEXT("bTraceComplex"), InParams.bTraceComplex);
	ULogUtilLib::LogInt32C(TEXT("IgnoreMask"), InParams.IgnoreMask);
	LogQueryMobilityTypeC(TEXT("MobilityType"), InParams.MobilityType);
	ULogUtilLib::LogNameC(TEXT("OwnerTag"), InParams.OwnerTag);
	M_TO_BE_IMPL(TEXT("Log StatId"));
	ULogUtilLib::LogNameC(TEXT("TraceTag"), InParams.TraceTag);
}

void UPhysUtilLib::LogCollisionQueryParamsIf(bool const bInShouldLog, const FCollisionQueryParams& InParams)
{
	if(bInShouldLog)
	{
		LogCollisionQueryParams(InParams);
	}
}


void UPhysUtilLib::LogComponentQueryParams(const FComponentQueryParams InParams)
{
	LogCollisionQueryParams(InParams);
}

void UPhysUtilLib::LogComponentQueryParamsIf(bool const bInShouldLog, const FComponentQueryParams& InParams)
{
	if(bInShouldLog)
	{
		LogComponentQueryParams(InParams);
	}
}


void UPhysUtilLib::LogQueryMobilityTypeC(const TCHAR* const InKey, EQueryMobilityType const InType)
{
	ULogUtilLib::LogStringC(InKey, *GetQueryMobilityTypeString(InType));
}

void UPhysUtilLib::LogQueryMobilityTypeIfC(bool const bInShouldLog, const TCHAR* const InKey, EQueryMobilityType const InType)
{
	if(bInShouldLog)
	{
		LogQueryMobilityTypeC(InKey, InType);
	}
}


void UPhysUtilLib::LogPlaneConstraintAxisSettingC(const TCHAR* const InKey, EPlaneConstraintAxisSetting const InValue)
{
	ULogUtilLib::LogStringC(InKey, GetPlaneConstraintAxisSettingString(InValue));
}

void UPhysUtilLib::LogPlaneConstraintAxisSettingIfC(bool const bInShouldLog, const TCHAR* const InKey, EPlaneConstraintAxisSetting const InValue)
{
	if(bInShouldLog)
	{
		LogPlaneConstraintAxisSettingC(InKey, InValue);
	}
}

void UPhysUtilLib::LogRadialImpulseFalloffC(const TCHAR* InKey, ERadialImpulseFalloff const InValue)
{
	ULogUtilLib::LogStringC(InKey, GetRadialImpulseFalloffString(InValue));
}

void UPhysUtilLib::LogRadialImpulseFalloffIfC(bool const bInShouldLog, const TCHAR* const InKey, ERadialImpulseFalloff const InValue)
{
	if(bInShouldLog)
	{
		LogRadialImpulseFalloffC(InKey, InValue);
	}
}

void UPhysUtilLib::LogCollisionResponseParams(const FCollisionResponseParams& InParams)
{
	M_TO_BE_IMPL(TEXT("Collision query"));
}

void UPhysUtilLib::LogCollisionChannelC(const TCHAR* const InKey, const ECollisionChannel InValue)
{
	ULogUtilLib::LogStringC(InKey, *GetCollisionChannelString(InValue));
}

void UPhysUtilLib::LogCollisionShape(const TCHAR* const InKey, const FCollisionShape& InValue)
{
	M_TO_BE_IMPL(TEXT("Collision shape"));
}


FString UPhysUtilLib::GetQueryMobilityTypeString(EQueryMobilityType const InType)
{
	return UTypeUtilLib::EnumToString<EQueryMobilityType>(InType);
}

FString UPhysUtilLib::GetCollisionChannelString(ECollisionChannel const InChannel)
{
	return UTypeUtilLib::EnumToString<ECollisionChannel>(InChannel);
}

FString UPhysUtilLib::GetPlaneConstraintAxisSettingString(EPlaneConstraintAxisSetting const InValue)
{
	return UTypeUtilLib::EnumToString<EPlaneConstraintAxisSetting>(InValue);
}

FString UPhysUtilLib::GetRadialImpulseFalloffString(ERadialImpulseFalloff const InValue)
{
	return UTypeUtilLib::EnumToString<ERadialImpulseFalloff>(InValue);
}
