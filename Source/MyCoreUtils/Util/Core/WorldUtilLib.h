#pragma once

#include "Log/MyLoggingTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "Engine/EngineTypes.h"

#include "WorldUtilLib.generated.h"

UENUM()
enum class ENewWorldFlags
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

	static FString GetWorldTypeString(EWorldType::Type InType);

	/**
	* Returns name of the map from the given world without streaming levels prefix.
	* @warning: world must be valid.
	*/
	UFUNCTION(BlueprintPure, Category = WorldUtil, Meta=(Deprecated, DeprecationMessage="GetMapName_NoStreamingPrefix is exta function! Use UGameplayStatics::GetCurrentLevelName(WorldContextObject, true)"))	
	static FString GetMapName_NoStreamingPrefix(UWorld* InWorld, ELogFlags InLogFlags = ELogFlags::None);
};