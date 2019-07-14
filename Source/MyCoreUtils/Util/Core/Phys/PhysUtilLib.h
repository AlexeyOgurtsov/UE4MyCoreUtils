#pragma once

#include "PhysUtilLibTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "CollisionQueryParams.h"
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

	static void LogQueryMobilityTypeC(const TCHAR* InKey, EQueryMobilityType InType);
	static void LogQueryMobilityTypeIfC(bool bInShouldLog, const TCHAR* InKey, EQueryMobilityType InType);

	static void LogCollisionResponseParams(const FCollisionResponseParams& InParams);
	static void LogCollisionChannelC(const TCHAR* InKey, const ECollisionChannel InValue);
	static void LogCollisionShape(const TCHAR* InKey, const FCollisionShape& InValue);

	static FString GetQueryMobilityTypeString(EQueryMobilityType InType);
	static FString GetCollisionChannelString(ECollisionChannel InChannel);
	// ~Log End
};
