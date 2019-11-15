#pragma once

#include "Util/Core/Misc/MyInterval.h"
#include "HelperAudioTypes.generated.h"

class USoundBase;

USTRUCT(BlueprintType, Category=Audio)
struct FMySoundMultiplierProps
{
	GENERATED_BODY()
	
	/** PitchMultiplier*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	FMyFloatInterval Pitch = FMyFloatInterval(0.5F, 2.0F);

	/** VolumeMultiplier*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	FMyFloatInterval Volume = FMyFloatInterval(0.8F, 1.5F);
};

USTRUCT(BlueprintType, Category=Audio)
struct FMySoundProps
{
	GENERATED_BODY()
	
	/** Sound*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	USoundBase* Sound = nullptr;

	/** Multiplier*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Audio)
	FMySoundMultiplierProps Multiplier;
	
};

