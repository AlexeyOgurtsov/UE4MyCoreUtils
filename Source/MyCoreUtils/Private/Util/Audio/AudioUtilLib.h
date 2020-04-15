#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "HelperAudioTypes.h"
#include "AudioUtilLib.generated.h"

class UAudioComponent;
class USoundBase;

UCLASS()
class UAudioUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static USoundBase* LoadInConstructorChecked(const TCHAR* ResourceName, const TCHAR* ResourcePath);
	static USoundBase* LoadInConstructor(const TCHAR* ResourceName, const TCHAR* ResourcePath);

	static USoundBase* LoadInConstructorChecked(UAudioComponent* AudioComponent, const TCHAR* ResourceName, const TCHAR* ResourcePath);
	static USoundBase* LoadInConstructor(UAudioComponent* AudioComponent, const TCHAR* ResourceName, const TCHAR* ResourcePath);
	

	/** PlayMySound
	 * Honors nullptr value for sound (no playing at that case)*/
	UFUNCTION(BlueprintCallable, Category=Audio, Meta=(WorldContext=WorldContextObject))
	static void PlayMySoundAtLocationIfShould(UObject* WorldContextObject, const FMySoundProps& InMySound, const FVector& InLocation, const FRotator& InRotator);

	/** SetAudioComponentFromMySoundMultiplier*/
	UFUNCTION(BlueprintCallable, Category=Audio)
	static void SetAudioComponentFromMySoundMultiplier(UAudioComponent* Component, const FMySoundMultiplierProps& Multiplier);
	
private:
};

// ~ RightHere_UAudioUtilLib Begin




// Adhoc impl lines (WARNING! move to .cpp file, otherwise will fail to compile!)
// ~ RightHere_UAudioUtilLib End

