#include "AudioUtilLib.h"
#include "Math/UnrealMathUtility.h"
#include "Math/Vector.h"
#include "Math/Rotator.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Util/Core/LogUtilLib.h"

USoundBase* UAudioUtilLib::LoadInConstructorChecked(const TCHAR* ResourceName, const TCHAR* ResourcePath)
{
	USoundBase* Sound = LoadInConstructor(ResourceName, ResourcePath);
	checkf(Sound != nullptr, TEXT("Resource load must succeed (checked)"));
	return Sound;
}

USoundBase* UAudioUtilLib::LoadInConstructor(const TCHAR* ResourceName, const TCHAR* ResourcePath)
{
	ConstructorHelpers::FObjectFinderOptional<USoundBase> AudioFinder { ResourcePath };
	M_LOG_ERROR_IF( ! AudioFinder.Succeeded(), TEXT("\"%s\" with path (\"%s\") NOT found"), ResourceName, ResourcePath);
	return AudioFinder.Get();
}

USoundBase* UAudioUtilLib::LoadInConstructorChecked(UAudioComponent* AudioComponent, const TCHAR* ResourceName, const TCHAR* ResourcePath)
{
	USoundBase* Sound = LoadInConstructor(AudioComponent, ResourceName, ResourcePath);
	checkf(Sound != nullptr, TEXT("Resource load must succeed (checked)"));
	return Sound;
}

USoundBase* UAudioUtilLib::LoadInConstructor(UAudioComponent* AudioComponent, const TCHAR* ResourceName, const TCHAR* ResourcePath)
{
	USoundBase* Loaded = LoadInConstructor(ResourceName, ResourcePath);
	if(Loaded != nullptr)
	{
		M_LOG(TEXT("\"%s\" with path \"%s\" found, setting it up"), ResourceName, ResourcePath);
		AudioComponent->SetSound(Loaded);
	}
	return Loaded;
}
	
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
