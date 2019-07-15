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
	LogCollisionShapeTypeC(*FString::Printf(TEXT("%s.ShapeType"), InKey), InValue.ShapeType);
	switch(InValue.ShapeType)
	{
	case ECollisionShape::Box:
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Box.HalfExtentX"), InKey), InValue.Box.HalfExtentX);
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Box.HalfExtentY"), InKey), InValue.Box.HalfExtentY);
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Box.HalfExtentZ"), InKey), InValue.Box.HalfExtentZ);
		break;

	case ECollisionShape::Sphere:
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Sphere.Radius"), InKey), InValue.Sphere.Radius);
		break;

	case ECollisionShape::Capsule:
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Capsule.Radius"), InKey), InValue.Capsule.Radius);
		ULogUtilLib::LogFloatC(*FString::Printf(TEXT("%s.Capsule.HalfHeight"), InKey), InValue.Capsule.HalfHeight);
		break;
	}
}


void UPhysUtilLib::LogCollisionShapeTypeC(const TCHAR* InKey, ECollisionShape::Type const InType)
{
	ULogUtilLib::LogStringC(InKey, GetCollisionShapeTypeString(InType));
}

void UPhysUtilLib::LogCollisionShapeTypeIfC(bool bInShouldLog, const TCHAR* InKey, ECollisionShape::Type const InType)
{
	if(bInShouldLog)
	{
		LogCollisionShapeTypeC(InKey, InType);
	}
}
FString UPhysUtilLib::GetQueryMobilityTypeString(EQueryMobilityType const InType)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<EQueryMobilityType>(InType);

	switch(InType)
	{
	case EQueryMobilityType::Any:
		return FString(TEXT("Any"));
	case EQueryMobilityType::Static:
		return FString(TEXT("Static"));
	case EQueryMobilityType::Dynamic:
		return FString(TEXT("Dynamic"));
	default:
		break;
	}
	return FString(TEXT("Unknown enum value"));
}

FString UPhysUtilLib::GetCollisionChannelString(ECollisionChannel const InChannel)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<ECollisionChannel>(InChannel);
	//
	switch(InChannel)
	{
	case ECC_WorldStatic:
		return FString(TEXT("WorldStatic"));
	case ECC_WorldDynamic:
		return FString(TEXT("WorldDynamic"));
	case ECC_Pawn:
		return FString(TEXT("Pawn"));
	case ECC_Visibility:
		return FString(TEXT("Visibility"));
	case ECC_Camera:
		return FString(TEXT("Camera"));
	case ECC_PhysicsBody:
		return FString(TEXT("PhysicsBody"));
	case ECC_Vehicle:
		return FString(TEXT("Vehicle"));
	case ECC_Destructible:
		return FString(TEXT("Destructible"));
	case ECC_EngineTraceChannel1:
		return FString(TEXT("EngineTraceChannel1"));
	case ECC_EngineTraceChannel2:
		return FString(TEXT("EngineTraceChannel2"));
	case ECC_EngineTraceChannel3:
		return FString(TEXT("EngineTraceChannel3"));
	case ECC_EngineTraceChannel4:
		return FString(TEXT("EngineTraceChannel4"));
	case ECC_EngineTraceChannel5:
		return FString(TEXT("EngineTraceChannel5"));
	case ECC_GameTraceChannel1:
		return FString(TEXT("GameTraceChannel1"));
	case ECC_GameTraceChannel2:
		return FString(TEXT("GameTraceChannel2"));
	case ECC_GameTraceChannel3:
		return FString(TEXT("GameTraceChannel3"));
	case ECC_GameTraceChannel4:
		return FString(TEXT("GameTraceChannel4"));
	case ECC_GameTraceChannel5:
		return FString(TEXT("GameTraceChannel5"));
	case ECC_GameTraceChannel6:
		return FString(TEXT("GameTraceChannel6"));
	case ECC_GameTraceChannel7:
		return FString(TEXT("GameTraceChannel7"));
	case ECC_GameTraceChannel8:
		return FString(TEXT("GameTraceChannel8"));
	case ECC_GameTraceChannel9:
		return FString(TEXT("GameTraceChannel9"));
	case ECC_GameTraceChannel10:
		return FString(TEXT("GameTraceChannel10"));
	case ECC_GameTraceChannel11:
		return FString(TEXT("GameTraceChannel11"));
	case ECC_GameTraceChannel12:
		return FString(TEXT("GameTraceChannel12"));
	case ECC_GameTraceChannel13:
		return FString(TEXT("GameTraceChannel13"));
	case ECC_GameTraceChannel14:
		return FString(TEXT("GameTraceChannel14"));
	case ECC_GameTraceChannel15:
		return FString(TEXT("GameTraceChannel15"));
	case ECC_GameTraceChannel16:
		return FString(TEXT("GameTraceChannel16"));
	case ECC_GameTraceChannel17:
		return FString(TEXT("GameTraceChannel17"));
	case ECC_GameTraceChannel18:
		return FString(TEXT("GameTraceChannel18"));
	case ECC_OverlapAll_Deprecated:
		return FString(TEXT("ECC_OverlapAll_Deprecated"));
	default:
		break;
	}
	return FString(TEXT("Unknown enum value"));
}

FString UPhysUtilLib::GetPlaneConstraintAxisSettingString(EPlaneConstraintAxisSetting const InValue)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<EPlaneConstraintAxisSetting>(InValue);
	//

	switch(InValue)
	{
	case EPlaneConstraintAxisSetting::Custom:
		return FString(TEXT("Custom"));

	case EPlaneConstraintAxisSetting::X:
		return FString(TEXT("X"));

	case EPlaneConstraintAxisSetting::Y:
		return FString(TEXT("Y"));

	case EPlaneConstraintAxisSetting::Z:
		return FString(TEXT("Z"));

	case EPlaneConstraintAxisSetting::UseGlobalPhysicsSetting:
		return FString(TEXT("UseGlobalPhysicsSetting"));

	default:
		break;
	}
	return FString(TEXT("Unknown enum value"));
}

FString UPhysUtilLib::GetRadialImpulseFalloffString(ERadialImpulseFalloff const InValue)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<ERadialImpulseFalloff>(InValue);
	
	switch(InValue)
	{
	case RIF_Constant:
		return FString(TEXT("Constant"));
	case RIF_Linear:
		return FString(TEXT("Linear"));
	case RIF_MAX:
		return FString(TEXT("MAX"));
	default:
		break;
	}
	return FString(TEXT("Unknown enum value"));
}

FString UPhysUtilLib::GetCollisionShapeTypeString(ECollisionShape::Type const InValue)
{
	switch(InValue)
	{
	case ECollisionShape::Type::Line:
		return FString(TEXT("Line"));
	case ECollisionShape::Type::Box:
		return FString(TEXT("Box"));
	case ECollisionShape::Type::Sphere:
		return FString(TEXT("Sphere"));
	case ECollisionShape::Type::Capsule:
		return FString(TEXT("Capsule"));
	default:
		break;
	}
	return FString(TEXT("Unknown enum value"));
}
