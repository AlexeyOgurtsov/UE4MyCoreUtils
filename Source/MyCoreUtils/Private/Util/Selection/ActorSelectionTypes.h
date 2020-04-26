#pragma once

#include "Containers/Set.h"
#include "CollisionQueryParams.h"
#include "CollisionShape.h"
#include "Engine/EngineTypes.h"
#include "ActorSelectionTypes.generated.h"

USTRUCT(BlueprintType)
struct FActorSelectionRule
{
	GENERATED_BODY()

	/**
	* Only actors pertaining to this set of classes will be allowed.
	* If empty, any actors to be allowed.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
	TSet<const UClass*> AllowedClasses;

	/**
	* Only actors containing this tags to be used.
	* If empty, any tags to be allowed.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
	TSet<FName> AllowedTags;

	// @TODO: Add restriction for filter (predicate-like) class
};

USTRUCT(BlueprintType)
struct FActorSelectionQuery
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	TEnumAsByte<ECollisionChannel> Channel = ECC_Visibility;

	FCollisionShape GetShape() const;
	const FCollisionQueryParams& GetQueryParams() const { return QueryParams; }
	const FCollisionResponseParams& GetResponseParams() const { return ResponseParams; }

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	float CapsuleRadius = 10000.0F;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	float CapsuleHalfHeight = 100.0F;

	FActorSelectionQuery();

private:
	FCollisionQueryParams QueryParams;
	FCollisionResponseParams ResponseParams;
};

USTRUCT(BlueprintType)
struct FActorSelectionRules
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	TArray<FActorSelectionRule> Rules;
};


USTRUCT(BlueprintType)
struct FActorSelectionProps
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	FActorSelectionRules Rule;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category=Selection)
	FActorSelectionQuery Query;
};
