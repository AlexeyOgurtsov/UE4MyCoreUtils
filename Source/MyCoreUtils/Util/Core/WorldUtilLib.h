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
enum class EMySpawnFlags : uint8
{
	None                             = 0             UMETA(DisplayName="None"),

	/**
	* If specified, the spawn actor utility function returns nullptr when fails,
	* otherwise, function asserts that UWorld::Spawn does NOT fail.
	*
	* @note: We need this flag, ever if there's bNoFail, because FActorSpawnParameters are not available in blueprints.
	*/
	AllowFail                        = 1 << 0        UMETA(DisplayName="Allow fail"),

	/**
	* Log maximum info about the created actor
	*/
	FullActorLog                     = 1 << 1        UMETA(DisplayName="Full actor log"),

	MaximalLogging                   = FullActorLog  UMETA(DisplayName="Maximal logging"),

	Default                          = None          UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(EMySpawnFlags);

UENUM()
enum class EWorldStringFlags : uint8
{
	None                             = 0             UMETA(DisplayName="None"),

	Default                          = None          UMETA(DisplayName="Default")
};
ENUM_CLASS_FLAGS(EWorldStringFlags);

UCLASS()
class UWorldUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	* Function for creating a functional UWorld,
	* typically to be used within the automation tests.
	*
	* @note: DestroyWorld (or DestroyWorldSafe) is to be used to destroy the world after creation!
	* @see DestroyWorldSafe
	*/
	static UWorld* NewWorldAndContext
	(
		EWorldType::Type InWorldType = EWorldType::Type::Game, 
		ENewWorldFlags InFlags = ENewWorldFlags::Default, 
		FName InWorldName = NAME_None,
		ELogFlags InLogFlags = ELogFlags::LogEverSuccess
	);

	/**
	* @see: NewWorldAndContext
	*/
	UFUNCTION(BlueprintCallable, Category = WorldUtil)
	static UWorld* NewGameWorldAndContext
	(
		ENewWorldFlags InFlags = ENewWorldFlags::Default, 
		FName InWorldName = NAME_None,
		ELogFlags InLogFlags = ELogFlags::LogEverSuccess
	);

	/**
	* Destroy the given world.
	* Automatically nullifies the given pointer to world.
	* @note: works correctly ever if world is nullptr.
	*/
	static void DestroyWorldSafe(UWorld** const ppInWorld, bool bInformEngineOrWorld = true, UWorld* InNewWorld = nullptr, ELogFlags InLogFlags = ELogFlags::LogEverSuccess);

	UFUNCTION(BlueprintCallable, Category = WorldUtil, Meta=(DisplayName="DestroyWorldSafe"))
	static void K2DestroyWorldSafe(UWorld* InWorld, bool bInformEngineOrWorld = true, UWorld* InNewWorld = nullptr, ELogFlags InLogFlags = ELogFlags::LogEverSuccess);

	// ~Spawn Begin
	template<class T>
	static T* Spawn
	(
		UWorld* const InWorld,
		const FTransform& InTransform,
		EMySpawnFlags const InFlags = EMySpawnFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{},
	       	ELogFlags const InLogFlags = ELogFlags::None
	)
	{
		return Cast<T>(Spawn(InWorld, T::StaticClass(), InTransform, InFlags, InSpawnParameters, InLogFlags));
	}

	template<class T>
	static T* Spawn
	(
		UWorld* const InWorld,
		const FVector& InLocation, const FRotator& InRotation = FRotator{0, 0, 0}, 
		EMySpawnFlags const InFlags = EMySpawnFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{}, 
		ELogFlags const InLogFlags = ELogFlags::None
	)
	{
		return Cast<T>(Spawn(InWorld, T::StaticClass(), InLocation, InRotation, InFlags, InSpawnParameters, InLogFlags));
	}

	static AActor* Spawn
	(
	 	UWorld* InWorld,
	 	UClass* InClass,
	       	const FTransform& InTransform, 
		EMySpawnFlags InFlags = EMySpawnFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{},
	       	ELogFlags InLogFlags = ELogFlags::None
	);

	static AActor* Spawn
	(
		UWorld* InWorld,
	 	UClass* InClass, 
		const FVector& InLocation, const FRotator& InRotation = FRotator{0, 0, 0}, 
		EMySpawnFlags InFlags = EMySpawnFlags::Default,
		const FActorSpawnParameters& InSpawnParameters = FActorSpawnParameters{}, 
		ELogFlags InLogFlags = ELogFlags::None
	);

	UFUNCTION(BlueprintCallable, Category = WorldUtil, Meta=(DisplayName="SpawnByTransform", WorldContext="InWorldContextObject"))
	static AActor* K2SpawnByTransform
	(
	 	UObject* InWorldContextObject,
	 	UClass* InClass,
	       	const FTransform& InTransform, 
		EMySpawnFlags InFlags = EMySpawnFlags::Default,
	       	ELogFlags InLogFlags = ELogFlags::None
	);

	UFUNCTION(BlueprintCallable, Category = WorldUtil, Meta=(DisplayName="Spawn", AutoCreateRefParam="InRotation", WorldContext="InWorldContextObject"))
	static AActor* K2Spawn
	(
	 	UObject* InWorldContextObject,
	 	UClass* InClass, 
		const FVector& InLocation, const FRotator& InRotation,
		EMySpawnFlags InFlags = EMySpawnFlags::Default,
		ELogFlags InLogFlags = ELogFlags::None
	);
	// ~Spawn End

	//UFUNCTION(BlueprintCallable, Category = WorldUtil)
	static FString GetWorldTypeString(EWorldType::Type InType);

	UFUNCTION(BlueprintPure, Category = WorldUtil)
	static FString GetWorldStringSafe(const UWorld* InWorld, EWorldStringFlags InFlags = EWorldStringFlags::Default);

	/**
	* Returns name of the map from the given world without streaming levels prefix.
	* @warning: world must be valid.
	*/
	UFUNCTION(BlueprintPure, Category = WorldUtil, Meta=(Deprecated, DeprecationMessage="GetMapName_NoStreamingPrefix is exta function! Use UGameplayStatics::GetCurrentLevelName(WorldContextObject, true)"))	
	static FString GetMapName_NoStreamingPrefix(UWorld* InWorld, ELogFlags InLogFlags = ELogFlags::None);
};
