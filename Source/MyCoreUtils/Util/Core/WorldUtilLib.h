#pragma once

#include "Log/MyLoggingTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/EngineTypes.h"

// FActorSpawnParameters (without this include compilation error on FActorSpawnParameters default initializer)
#include "Engine/World.h" 

#include "WorldUtilLib.generated.h"

UENUM()
enum class ENewWorldFlags : uint8
{
	None                             = 0             UMETA(DisplayName = "None"),
	SkipContextCreation              = 1 << 0        UMETA(DisplayName="Skip context creation"),	

	/**
	* Corresponds to UWorld::CreateWorld's argument bNotifyEngineOrWorld
	* (opposite to it, really)
	*/
	SkipNotifyEngine                 = 1 << 1        UMETA(DisplayName="Skip notify engine"), 

	/**
	* Skip calling UWorld::InitializeActorsForPlay(FURL)
	*/
	SkipInitializeActors             = 1 << 2       UMETA(DisplayName="Skip initialize actors"),

	/**
	* Skip calling UWorld::BeginPlay
	*/
	SkipBeginPlay                    = 1 << 3       UMETA(DisplayName="Skip BeginPlay"),

	/**
	* Corresponds to bAddToRoot argument of the UWorld::CreateWorld
	* (opposite to it, really)
	*/
	SkipAddToRoot                    = 1 << 4        UMETA(DisplayName="Skip add to root"),
	
	Default                          = None          UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(ENewWorldFlags);

UENUM()
enum class EMySpawnActorFlags : uint8
{
	None                             = 0             UMETA(DisplayName="None"),

	/**
	* If specified, the spawn actor utility function returns nullptr when fails,
	* otherwise, function asserts that UWorld::SpawnActor does NOT fail.
	*
	* @note: We need this flag, ever if there's bNoFail, because FActorSpawnParameters are not available in blueprints.
	*/
	AllowFail                        = 1 << 0        UMETA(DisplayName="Allow fail"),

	/**
	* Log maximum info about the created actor
	*/
	FullActorLog                     = 1 << 1        UMETA(DisplayName="Full actor log"),

	Default                          = None
};
ENUM_CLASS_FLAGS(EMySpawnActorFlags);

UCLASS()
class UWorldUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Function for creating a functional UWorld,
	* typically to be used within the automation tests.
	*
	* @note: DestroyWorld is to be used to destroy the world after creation!
	*/
	static UWorld* NewWorldAndContext
	(
		EWorldType::Type InWorldType = EWorldType::Type::Game, 
		ENewWorldFlags InFlags = ENewWorldFlags::Default, 
		FName InWorldName = NAME_None,
		ELogFlags InLogFlags = ELogFlags::LogEverSuccess
	);

	UFUNCTION(BlueprintCallable, Category = WorldUtil)
	static UWorld* NewGameWorldAndContext
	(
		ENewWorldFlags InFlags = ENewWorldFlags::Default, 
		FName InWorldName = NAME_None,
		ELogFlags InLogFlags = ELogFlags::LogEverSuccess
	);

	// ~SpawnActor Begin
	template<class T> T* SpawnActor
	(
		UWorld* const InWorld,
		const FTransform& InTransform,
		EMySpawnActorFlags const InFlags = EMySpawnActorFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{},
	       	ELogFlags const InLogFlags = ELogFlags::None
	)
	{
		return Cast<T>(SpawnActor(InWorld, T::StaticClass(), InTransform, InFlags, InSpawnParameters, InLogFlags));
	}

	template<class T>
	T* SpawnActor
	(
		UWorld* const InWorld,
		const FVector& InLocation, const FRotator& InRotation = FRotator{0, 0, 0}, 
		EMySpawnActorFlags const InFlags = EMySpawnActorFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{}, 
		ELogFlags const InLogFlags = ELogFlags::None
	)
	{
		return Cast<T>(SpawnActor(InWorld, T::StaticClass(), InLocation, InRotation, InFlags, InSpawnParameters, InLogFlags));
	}

	AActor* SpawnActor
	(
	 	UWorld* InWorld,
	 	UClass* InClass,
	       	const FTransform& InTransform, 
		EMySpawnActorFlags InFlags = EMySpawnActorFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{},
	       	ELogFlags InLogFlags = ELogFlags::None
	);

	AActor* SpawnActor
	(
		UWorld* InWorld,
	 	UClass* InClass, 
		const FVector& InLocation, const FRotator& InRotation = FRotator{0, 0, 0}, 
		EMySpawnActorFlags InFlags = EMySpawnActorFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{}, 
		ELogFlags InLogFlags = ELogFlags::None
	);

	UFUNCTION(BlueprintCallable, Category = WorldUtil, Meta=(DisplayName="SpawnActorByTransform", WorldContext="InWorldContextObject"))
	AActor* K2SpawnActorByTransform
	(
	 	UObject* InWorldContextObject,
	 	UClass* InClass,
	       	const FTransform& InTransform, 
		EMySpawnActorFlags InFlags = EMySpawnActorFlags::Default,
	       	ELogFlags InLogFlags = ELogFlags::None
	);

	UFUNCTION(BlueprintCallable, Category = WorldUtil, Meta=(DisplayName="SpawnActor", AutoCreateRefParam="InRotation", WorldContext="InWorldContextObject"))
	AActor* K2SpawnActor
	(
	 	UObject* InWorldContextObject,
	 	UClass* InClass, 
		const FVector& InLocation, const FRotator& InRotation,
		EMySpawnActorFlags InFlags = EMySpawnActorFlags::Default,
		ELogFlags InLogFlags = ELogFlags::None
	);
	// ~SpawnActor End

	//UFUNCTION(BlueprintCallable, Category = WorldUtil)
	static FString GetWorldTypeString(EWorldType::Type InType);

	/**
	* Returns name of the map from the given world without streaming levels prefix.
	* @warning: world must be valid.
	*/
	UFUNCTION(BlueprintPure, Category = WorldUtil, Meta=(Deprecated, DeprecationMessage="GetMapName_NoStreamingPrefix is exta function! Use UGameplayStatics::GetCurrentLevelName(WorldContextObject, true)"))	
	static FString GetMapName_NoStreamingPrefix(UWorld* InWorld, ELogFlags InLogFlags = ELogFlags::None);
};
