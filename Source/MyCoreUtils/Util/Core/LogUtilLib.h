#pragma once

#include "MyDebugMacros.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LogUtilLib.generated.h"

UCLASS()
class ULogUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	ULogUtilLib();


	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is invalid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClass(UObject* InObject);

	/**
	* Returns name and class of the object.
	* WARNING: nullptr object is valid.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassSafe(UObject* InObject);

	/**
	* Returns name and class of the object, enclosed in brackets.
	*/
	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetNameAndClassScoped(UObject* InObject);

	UFUNCTION(BlueprintPure, Category = Log)
	static FString GetYesNo(bool bYes);
};

// ~Logging macros End