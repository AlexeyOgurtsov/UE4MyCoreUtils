#pragma once

#include "Util/Audio/HelperAudioTypes.h"
#include "TUProjectileConfigProps.generated.h"

USTRUCT(BlueprintType, Category=Projectile)
struct FTUProjectileAudioConfigProps
{
	GENERATED_BODY()

	/** HitSound*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	FMySoundProps HitSound;

	/** FlySound*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	FMySoundMultiplierProps FlyMultiplier;
};


USTRUCT(BlueprintType, Category=Projectile)
struct FTUProjectileConfigProps
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Projectile)
	FTUProjectileAudioConfigProps Audio;
};

