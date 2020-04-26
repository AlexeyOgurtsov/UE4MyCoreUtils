#pragma once

#include "ActorSelectionTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Util/Selection/ActorSelectionTypes.h"
#include "ActorSelectionLib.generated.h"

UCLASS(BlueprintType)
class UActorSelectionLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Selects all classes from the given actor as the center point.
	* Actor is always ignored.
	*/
	UFUNCTION(BlueprintCallable, Category=Selection)
	static TSet<AActor*> SelectAtActor
	(
	 	AActor* CenterObject,
		const FActorSelectionProps& SelectionProps
	);	

	UFUNCTION(BlueprintCallable, Category=Selection, Meta=(WorldContext=WorldContextObject))
	static TSet<AActor*> SelectAtPoint
	(
	 	const FVector& Point, 
		const FActorSelectionProps& SelectionProps,
	 	UObject* WorldContextObject,
		const TSet<AActor*>& IgnoreActors 
	);	

	UFUNCTION(BlueprintPure, Category = Selection)
	static bool ShouldActorBeSelected(const AActor* Actor, const FActorSelectionRules& SelectionRules);

	UFUNCTION(BlueprintCallable, Category = Selection, Meta=(WorldContext=WorldContextObject))
	static bool OverlapMultiByChannel(TSet<AActor*>& OutOverlappedActors, const FVector& Point, const FActorSelectionQuery& Query, UObject* WorldContextObject);

private:
	static void FilterOutBySelectionRules(TSet<AActor*>& OutActors, const FActorSelectionRules& Rules);	

	static void OverlapResultArrayToActorSet(const TArray<FOverlapResult>& Overlaps, TSet<AActor*>& OutOverlappedActor);
};
