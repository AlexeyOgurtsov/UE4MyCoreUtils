#pragma once

#include "PhysUtilLibTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "PhysUtilLib.generated.h"

UCLASS()
class UPhysUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ~Log Begin
	UFUNCTION(BlueprintCallable, Category = "Phys|Log")
	static void LogHitResult(const FHitResult& InHitResult, ELogHitFlags InFlags = ELogHitFlags::Default);
	
	UFUNCTION(BlueprintCallable, Category = "Phys|Log")
	static void LogHitResultIf(bool bInShouldLog, const FHitResult& InHitResult, ELogHitFlags InFlags = ELogHitFlags::Default);
	// ~Log End
};
