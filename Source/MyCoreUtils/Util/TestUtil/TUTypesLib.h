#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TUTypes.h"
#include "TUTypesLib.generated.h"

UCLASS()
class UTUTypesLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "TUTypesLib")
	static FString GetTUFlagsString(ETUFlags InFlags);

	UFUNCTION(BlueprintCallable, Category = "TUTypesLib")
	static void LogTUFlags(ETUFlags InFlags);
};