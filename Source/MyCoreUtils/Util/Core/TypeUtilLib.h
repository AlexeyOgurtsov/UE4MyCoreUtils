#pragma once

#include "Misc/Optional.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TypeUtilLib.generated.h"

UCLASS()
class UTypeUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// ~Enums Begin
	/**
	* If enum with the given name or literal does not exist, otherwise returns negative, 
	* otherwise returns enum's literal value.
	*/
	UFUNCTION(BlueprintPure, Category = TypeUtilLib)
	static int32 FindEnumIndexByName(const FString& InEnumName, const FString& InString);

	/**
	* Returns enum literal value.
	* @warning: the literal and enum value must exist.
	* @see: FindEnumIndexByName
	*/
	UFUNCTION(BlueprintPure, Category = TypeUtilLib)
	static int32 FindEnumIndexByNameChecked(const FString& InEnumName, const FString& InString);
	// ~Enums End
};