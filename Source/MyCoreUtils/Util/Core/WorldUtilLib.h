#pragma once

#include "Log/MyLoggingTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WorldUtilLib.generated.h"

UCLASS()
class UWorldUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Returns name of the map from the given world without streaming levels prefix.
	* @warning: world must be valid.
	*/
	UFUNCTION(BlueprintPure, Category = WorldUtilLib)	
	static FString GetMapName_NoStreamingPrefix(UWorld* InWorld, ELogFlags InLogFlags = ELogFlags::None);
};