#include "PhysUtilLib.h"
#include "GameFramework/Actor.h" // For casts
#include "Components/PrimitiveComponent.h" // For casts
#include "PhysicalMaterials/PhysicalMaterial.h" // For casts
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
