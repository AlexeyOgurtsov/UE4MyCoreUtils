#include "PhysUtilLib.h"
#include "GameFramework/Actor.h" // For casts
#include "Components/PrimitiveComponent.h" // For casts
#include "PhysicalMaterials/PhysicalMaterial.h" // For casts
#include "WorldCollision.h"
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

void UPhysUtilLib::LogCollisionQueryParamsIf(bool bInShouldLog, const FCollisionQueryParams& InParams)
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

void UPhysUtilLib::LogComponentQueryParamsIf(bool bInShouldLog, const FComponentQueryParams& InParams)
{
	if(bInShouldLog)
	{
		LogComponentQueryParams(InParams);
	}
}


void UPhysUtilLib::LogQueryMobilityTypeC(const TCHAR* InKey, EQueryMobilityType InType)
{
	ULogUtilLib::LogStringC(InKey, *GetQueryMobilityTypeString(InType));
}

void UPhysUtilLib::LogQueryMobilityTypeIfC(bool bInShouldLog, const TCHAR* InKey, EQueryMobilityType InType)
{
	if(bInShouldLog)
	{
		LogQueryMobilityTypeC(InKey, InType);
	}
}


void UPhysUtilLib::LogCollisionResponseParams(const FCollisionResponseParams& InParams)
{
	M_TO_BE_IMPL(TEXT("Collision query"));
}

void UPhysUtilLib::LogCollisionChannelC(const TCHAR* InKey, const ECollisionChannel InValue)
{
	ULogUtilLib::LogStringC(InKey, *GetCollisionChannelString(InValue));
}

void UPhysUtilLib::LogCollisionShape(const TCHAR* InKey, const FCollisionShape& InValue)
{
	M_TO_BE_IMPL(TEXT("Collision shape"));
}


FString UPhysUtilLib::GetQueryMobilityTypeString(EQueryMobilityType InType)
{
	M_NOT_IMPL_RET(FString(TEXT("{not impl}")));
}

FString UPhysUtilLib::GetCollisionChannelString(ECollisionChannel InChannel)
{
	M_NOT_IMPL_RET(FString(TEXT("{not impl}")));
}

