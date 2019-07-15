#pragma once

#include "PhysUtilLibTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "WorldCollision.h" // ECollisionShape::Type
#include "CollisionQueryParams.h"
#include "GameFramework/MovementComponent.h" // EPlaneConstraintAxisSetting
#include "PhysUtilLib.generated.h"

struct FCollisionShape;

UCLASS()
class UPhysUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ~Log Begin
	UFUNCTION(BlueprintCallable, Category = "Phys|Collision|Log")
	static void LogHitResult(const FHitResult& InHitResult, ELogHitFlags InFlags = ELogHitFlags::Default);
	
	UFUNCTION(BlueprintCallable, Category = "Phys|Collision|Log")
	static void LogHitResultIf(bool bInShouldLog, const FHitResult& InHitResult, ELogHitFlags InFlags = ELogHitFlags::Default);

	static void LogCollisionQueryParams(const FCollisionQueryParams& InParams);
	static void LogCollisionQueryParamsIf(bool bInShouldLog, const FCollisionQueryParams& InParams);

	static void LogComponentQueryParams(const FComponentQueryParams InParams);
	static void LogComponentQueryParamsIf(bool bInShouldLog, const FComponentQueryParams& InParams);

	static void LogCollisionShapeTypeC(const TCHAR* InKey, ECollisionShape::Type InType);
	static void LogCollisionShapeTypeIfC(bool bInShouldLog, const TCHAR* InKey, ECollisionShape::Type InType);

	static void LogQueryMobilityTypeC(const TCHAR* InKey, EQueryMobilityType InType);
	static void LogQueryMobilityTypeIfC(bool bInShouldLog, const TCHAR* InKey, EQueryMobilityType InType);

	static void LogPlaneConstraintAxisSettingC(const TCHAR* InKey, EPlaneConstraintAxisSetting InValue);
	static void LogPlaneConstraintAxisSettingIfC(bool bInShouldLog, const TCHAR* InKey, EPlaneConstraintAxisSetting InValue);

	static void LogRadialImpulseFalloffC(const TCHAR* InKey, ERadialImpulseFalloff InValue);
	static void LogRadialImpulseFalloffIfC(bool bInShouldLog, const TCHAR* InKey, ERadialImpulseFalloff InValue);

	static void LogCollisionResponseParams(const FCollisionResponseParams& InParams);
	static void LogCollisionChannelC(const TCHAR* InKey, const ECollisionChannel InValue);
	static void LogCollisionShape(const TCHAR* InKey, const FCollisionShape& InValue);

	static FString GetQueryMobilityTypeString(EQueryMobilityType InType);
	static FString GetCollisionChannelString(ECollisionChannel InChannel);

	static FString GetPlaneConstraintAxisSettingString(EPlaneConstraintAxisSetting InValue);

	static FString GetRadialImpulseFalloffString(ERadialImpulseFalloff InValue);

	static FString GetCollisionShapeTypeString(ECollisionShape::Type InValue);
	// ~Log End
};
