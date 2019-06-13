#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyComponentLib.generated.h"

class AActor;

UCLASS()
class UMyComponentLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Call BindOwner for all direct child components.
	*/
	UFUNCTION(BlueprintCallable, Category = Components)
	static void BindAllComponentsToOwner(AActor* InOwner);

	/**
	* Call OwnerReady for all direct child components.
	*/
	UFUNCTION(BlueprintCallable, Category = Components)
	static void NotifyOwnerReady(AActor* InOwner);
};