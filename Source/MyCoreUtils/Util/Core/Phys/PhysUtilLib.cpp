#include "PhysUtilLib.h"
#include "GameFramework/Actor.h" // For casts
#include "Components/PrimitiveComponent.h" // For casts
#include "PhysicalMaterials/PhysicalMaterial.h" // For casts
#include "WorldCollision.h"
#include "Util/Core/TypeUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "Util/Core/SystemUtils.h"


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

	#define M_CASE_PREFIX() EQueryMobilityType::
	M_SWITCH_BEGIN(InType)
		M_CASE_ENUM_PREFIX_STRING(Any);
		M_CASE_ENUM_PREFIX_STRING(Static);
		M_CASE_ENUM_PREFIX_STRING(Dynamic);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}

FString UPhysUtilLib::GetCollisionChannelString(ECollisionChannel const InChannel)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<ECollisionChannel>(InChannel);

	#define M_CASE_PREFIX() ECC_
	M_SWITCH_BEGIN(InChannel)	
		M_CASE_ENUM_PREFIX_STRING(WorldStatic);
		M_CASE_ENUM_PREFIX_STRING(WorldDynamic);
		M_CASE_ENUM_PREFIX_STRING(Pawn);
		M_CASE_ENUM_PREFIX_STRING(Visibility);
		M_CASE_ENUM_PREFIX_STRING(Camera);
		M_CASE_ENUM_PREFIX_STRING(PhysicsBody);
		M_CASE_ENUM_PREFIX_STRING(Vehicle);
		M_CASE_ENUM_PREFIX_STRING(Destructible);
		M_CASE_ENUM_PREFIX_STRING(EngineTraceChannel1);
		M_CASE_ENUM_PREFIX_STRING(EngineTraceChannel2);
		M_CASE_ENUM_PREFIX_STRING(EngineTraceChannel3);
		M_CASE_ENUM_PREFIX_STRING(EngineTraceChannel4);
		M_CASE_ENUM_PREFIX_STRING(EngineTraceChannel5);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel1);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel2);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel3);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel4);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel5);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel6);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel7);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel8);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel9);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel10);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel11);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel12);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel13);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel14);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel15);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel16);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel17);
		M_CASE_ENUM_PREFIX_STRING(GameTraceChannel18);
		M_CASE_ENUM_PREFIX_STRING(OverlapAll_Deprecated);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}

FString UPhysUtilLib::GetPlaneConstraintAxisSettingString(EPlaneConstraintAxisSetting const InValue)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<EPlaneConstraintAxisSetting>(InValue);
	
	#define M_CASE_PREFIX() EPlaneConstraintAxisSetting::
	M_SWITCH_BEGIN(InValue)	
		M_CASE_ENUM_PREFIX_STRING(Custom);
		M_CASE_ENUM_PREFIX_STRING(X);
		M_CASE_ENUM_PREFIX_STRING(Y);
		M_CASE_ENUM_PREFIX_STRING(Z);
		M_CASE_ENUM_PREFIX_STRING(UseGlobalPhysicsSetting);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}

FString UPhysUtilLib::GetRadialImpulseFalloffString(ERadialImpulseFalloff const InValue)
{
	// StaticEnum fails to compile
	//return UTypeUtilLib::EnumToString<ERadialImpulseFalloff>(InValue);
	
	#define M_CASE_PREFIX() RIF_
	M_SWITCH_BEGIN(InValue)	
		M_CASE_ENUM_PREFIX_STRING(Constant);
		M_CASE_ENUM_PREFIX_STRING(Linear);
		M_CASE_ENUM_PREFIX_STRING(MAX);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}

FString UPhysUtilLib::GetCollisionShapeTypeString(ECollisionShape::Type const InValue)
{
	#define M_CASE_PREFIX() ECollisionShape::Type::
	M_SWITCH_BEGIN(InValue)	
		M_CASE_ENUM_PREFIX_STRING(Line);
		M_CASE_ENUM_PREFIX_STRING(Box);
		M_CASE_ENUM_PREFIX_STRING(Sphere);
		M_CASE_ENUM_PREFIX_STRING(Capsule);
	M_SWITCH_END_DEFAULT_WRONG_ENUM_STRING()
	#undef M_CASE_PREFIX
}
