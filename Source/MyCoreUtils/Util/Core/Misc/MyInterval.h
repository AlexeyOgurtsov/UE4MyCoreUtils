#pragma once

#include "MyInterval.generated.h"

USTRUCT(BlueprintType)
struct FMyFloatInterval
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Min = 0.0F;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max = 1.0F;

	FMyFloatInterval() 
	{
	}

	FMyFloatInterval(float InMin, float InMax)
	: Min (InMin)
	, Max (InMax)
	{
	}
};
