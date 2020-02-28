#pragma once

#include "UObject/Interface.h"
#include "IMyComponent.generated.h"

class AActor;

UINTERFACE()
class UMyComponent : public UInterface
{
	GENERATED_BODY()
};

class IMyComponent
{
	GENERATED_BODY()

public:
	/**
	* To be called as soon as possible to bind the owning actor to the component
	* (We need this way as GetTypedOuter() does NOT work inside the constructor).
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Initialization)
	void BindOwner(AActor* InOwner);

	/**
	* To be called just when the owner object is ready (but components are not yet).
	* Typically called at the end of BeginPlay.
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Play)
	void OwnerReady(AActor* InOwner);
};