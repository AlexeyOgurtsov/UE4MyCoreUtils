#include "AudioUtilLib.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

void UAudioUtilLib::PlayMySoundAtLocationIfShould(UObject* WorldContextObject, const FMySoundProps& InMySound, const FVector& InLocation, const FRotator& InRotator)
{
	if(InMySound.Sound)
	{
		float const PitchMultiplier = FMath::RandRange(InMySound.Multiplier.Pitch.Min, InMySound.Multiplier.Pitch.Max);
		float const VolumeMultiplier = FMath::RandRange(InMySound.Multiplier.Volume.Min, InMySound.Multiplier.Volume.Max);
		UGameplayStatics::PlaySoundAtLocation
		(
			WorldContextObject, InMySound.Sound,
			InLocation, InRotator, VolumeMultiplier, PitchMultiplier
		);
	}
}

void UAudioUtilLib::SetAudioComponentFromMySoundMultiplier(UAudioComponent* const Component, const FMySoundMultiplierProps& Multiplier)
{
	checkf(Component, TEXT("When calling \"%s\" passed component must valid NON-null pointer"), TEXT(__FUNCTION__));

	float const PitchMultiplier = FMath::RandRange(Multiplier.Pitch.Min, Multiplier.Pitch.Max);
	float const VolumeMultiplier = FMath::RandRange(Multiplier.Volume.Min, Multiplier.Volume.Max);
	Component->SetVolumeMultiplier(VolumeMultiplier);
	Component->SetPitchMultiplier(PitchMultiplier);
}
