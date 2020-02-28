#include "WorldUtilLib.h"
#include "LogUtilLib.h"

#include "Engine/World.h"
#include "Engine/Engine.h"	

UWorld* UWorldUtilLib::NewWorldAndContext
(
	EWorldType::Type const InWorldType,
	ENewWorldFlags const InFlags,
	FName const InWorldName,
	ELogFlags const InLogFlags
)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);
	ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("WorldType"), GetWorldTypeString(InWorldType));
	ULogUtilLib::LogNameIfFlagsC(InLogFlags, TEXT("WorldName"), InWorldName);

	if( GEngine == nullptr )
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GEngine is nullptr"));
		return nullptr;
	}

	bool const bInformEngineOrWorld = (InFlags & ENewWorldFlags::SkipNotifyEngine) == ENewWorldFlags::None;
	bool const bAddToRoot = (InFlags & ENewWorldFlags::SkipAddToRoot) == ENewWorldFlags::None;

	UWorld* W = nullptr;
	{
		M_LOGBLOCK_IF_FLAGS(InLogFlags, TEXT("UWorld::CreateWorld"));
		W = UWorld::CreateWorld(InWorldType, bInformEngineOrWorld, InWorldName, /*Package*/nullptr, bAddToRoot);
		if(W == nullptr)
		{
			M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("UWorld::CreateWorld returned nullptr"));
			return nullptr;
		}
		else
		{
			M_LOG(TEXT("World Created"));
			ULogUtilLib::LogObjectSafe(W);
		}
	}

	{
		bool const bCreateContext = (InFlags & ENewWorldFlags::SkipContextCreation) == ENewWorldFlags::None;

		if(bCreateContext)
		{
			M_LOG_IF_FLAGS(InLogFlags, TEXT("Creating FWorldContext (Due to flags)"));
			M_LOGBLOCK_IF_FLAGS(InLogFlags, TEXT("Calling UEngine::CreateNewWorldContext"));
			FWorldContext* const Context = &GEngine->CreateNewWorldContext(InWorldType);

			if(Context == nullptr)
			{
				M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("UEngine::CreateNewWorldContext returned nullptr"));
				return nullptr;
			}
			else
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("UEngineCreateNewWorldContext succeeded"));
			}

			Context->SetCurrentWorld(W);
		}
	}

	{
		bool const bInitializeActors = (InFlags & ENewWorldFlags::SkipInitializeActors) == ENewWorldFlags::None;
		if(bInitializeActors)
		{
			M_LOG_IF_FLAGS(InLogFlags, TEXT("Initializing actors (Due to flags)"));
			M_LOGBLOCK_IF_FLAGS(InLogFlags, TEXT("Calling UWorld::InitializeActorsForPlay"));

			FURL URL;
			W->InitializeActorsForPlay(URL, /*bResetTime*/true);
		}
	}

	{		
		bool const bBeginPlay = (InFlags & ENewWorldFlags::SkipBeginPlay) == ENewWorldFlags::None;
		if(bBeginPlay)
		{
			M_LOG_IF_FLAGS(InLogFlags, TEXT("Calling UWorld::BeginPlay (Due to flags)"));
			M_LOGBLOCK_IF_FLAGS(InLogFlags, TEXT("Calling UWorld::BeginPlay"));

			W->BeginPlay();

		}

		// WARNING! We should NOT log HasBegunPlay here, because the BeginPlay call will be delayed by several frames,
		// so logging may only confuse (it will always be false).
		//ULogUtilLib::LogYesNoIfFlagsC(InLogFlags, TEXT("HasBegunPlay of world is "), W->HasBegunPlay());
	}
	
	return W;
}	

UWorld* UWorldUtilLib::NewGameWorldAndContext
(
	ENewWorldFlags const InFlags,
	FName const InWorldName,
	ELogFlags const InLogFlags
)
{
	return NewWorldAndContext(EWorldType::Type::Game, InFlags, InWorldName, InLogFlags);
}
void UWorldUtilLib::K2DestroyWorldSafe(UWorld* const InWorld, bool const bInformEngineOrWorld, UWorld* const InNewWorld, ELogFlags const InLogFlags)
{
	FString const WorldString = GetWorldStringSafe(InWorld);

	M_LOGFUNC_MSG_IF_FLAGS(InLogFlags, TEXT("DestroyWorld {%s}"), *WorldString);
	ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("NewWorld"), GetWorldStringSafe(InNewWorld));
	ULogUtilLib::LogYesNoIfFlagsC(InLogFlags, TEXT("bInformEngineOrWorld"), bInformEngineOrWorld);

	if(InWorld)
	{
		M_LOGBLOCK_IF_FLAGS(InLogFlags, TEXT("Calling UWorld::DestroyWorld"));
		InWorld->DestroyWorld(bInformEngineOrWorld, InNewWorld);
	}		
}

void UWorldUtilLib::DestroyWorldSafe(UWorld** const ppInWorld, bool const bInformEngineOrWorld, UWorld* const InNewWorld, ELogFlags const InLogFlags)
{
	checkf(ppInWorld, TEXT("%s requires non-NULL pointer to UWorld pointer to be passed"), TEXT(__FUNCTION__));

	K2DestroyWorldSafe(*ppInWorld, bInformEngineOrWorld, InNewWorld, InLogFlags);

	*ppInWorld = nullptr;
}

FString UWorldUtilLib::GetWorldStringSafe(const UWorld* const InWorld, EWorldStringFlags const InFlags)
{
	if(InWorld == nullptr) 
	{
		return FString(TEXT(""));
	}

	TArray<FStringFormatArg> Args;
	Args.Add(InWorld->GetName());
	Args.Add(GetWorldTypeString(InWorld->WorldType));
	return FString::Format(TEXT("World named \"{0}\" of type \"{1}\""), Args);
}

FString UWorldUtilLib::GetWorldTypeString(EWorldType::Type const InType)
{
	switch(InType)
	{
	case EWorldType::Type::None:
		return FString(TEXT("None"));
	case EWorldType::Type::Game:
		return FString(TEXT("Game"));
	case EWorldType::Type::Editor:
		return FString(TEXT("Editor"));
	case EWorldType::Type::PIE:
		return FString(TEXT("PIE"));
	case EWorldType::Type::EditorPreview:
		return FString(TEXT("EditorPreview"));
	case EWorldType::Type::GamePreview:
		return FString(TEXT("GamePreview"));
	case EWorldType::Type::GameRPC:
		return FString(TEXT("GameRPC"));
	case EWorldType::Type::Inactive:
		return FString(TEXT("Inactive"));
	default:
		break;
	}
	return FString(TEXT("{Unknown world type}"));
}
	
TSet<AActor*> UWorldUtilLib::GetActorsByPredicate(UWorld* const InWorld, TFunction<bool(const AActor*)> const InPredicate, EActorIteratorFlags const InFlags)
{
	checkf(InWorld, TEXT("When calling %s World must be non-NULL pointer"), TEXT(__FUNCTION__));

	TSet<AActor*> S;
	for(AActor* A : TActorRange<AActor>(InWorld, AActor::StaticClass(), InFlags))
	{
		if(InPredicate(A))
		{
			S.Add(A);
		}
	}
	
	return S;
}

bool UWorldUtilLib::DestroyActors(const TSet<AActor*>& InActors, TSet<AActor*>* const pOutErrorActors, ELogFlags const InLogFlags)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);

	int32 const TotalActors = InActors.Num();
	M_LOG_IF_FLAGS(InLogFlags, TEXT("Total %d actors to process"), TotalActors);

	int32 NumFailedActors = 0;
	for(AActor* A : InActors)
	{
		if( A == nullptr )
		{
			continue;
		}
		if( ! A->Destroy() )
		{
			NumFailedActors++;
			if(pOutErrorActors)
			{
				pOutErrorActors->Add(A);
			}
			M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("Actor {%s}: AActor::Destroy returned false"), *ULogUtilLib::GetNameAndClassSafe(A));
		}
	}	

	int32 const CountDestroyed = TotalActors - NumFailedActors;
	M_LOG_IF_FLAGS(InLogFlags, TEXT("Summary: %d actors destroyed, %d actors failed (total %d actors)"), CountDestroyed, NumFailedActors, TotalActors);
	return (NumFailedActors == 0);
}

bool UWorldUtilLib::PurgeWorld
(
	UWorld* const InWorld, 
	TSet<const UClass*>* pInExcludeSet,
	TSet<AActor*>* const pOutErrorActors,
	EActorIteratorFlags InActorIteratorFlags,
	EMyActorSelectionFlags const InFlags,
	ELogFlags const InLogFlags
)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);

	if(pInExcludeSet == nullptr)
	{
		pInExcludeSet = GetPurgeDefaultExcludeSet();
	}	

	M_LOG_IF_FLAGS(InLogFlags, TEXT("%d classes in exclude set"), pInExcludeSet->Num());
	for(const UClass* ExcludeClass : *pInExcludeSet)
	{
		checkf(ExcludeClass, TEXT("Exclude set must contain only non-NULL pointers"));
		M_LOG_IF_FLAGS(InLogFlags, TEXT("ExcludeClass: %s"), *ExcludeClass->GetName());
	}

	TSet<AActor*> Actors = GetActorsByPredicate
	(
		InWorld, 
		[pInExcludeSet, InFlags, InLogFlags](const AActor* InActor) -> bool
		{
			if(nullptr == InActor)
			{
				return false;
			}	
			bool bInExcludeSet = false;
			for(const UClass* ExcludeClass : *pInExcludeSet)
			{
				checkf(ExcludeClass, TEXT("Exclude set must contain only non-NULL pointers"));
				if(InActor->GetClass()->IsChildOf(ExcludeClass))
				{
					bInExcludeSet = true;
					break;
				}
			}
			if(bInExcludeSet)
			{
				M_LOG_IF_FLAGS(InLogFlags, TEXT("Actor {%s}: skipping - class in exclude set"), *ULogUtilLib::GetNameAndClassSafe(InActor));
				return false;
			}
			return true;
		},
		InActorIteratorFlags
	);
	return DestroyActors(Actors, pOutErrorActors, InLogFlags);
}

AActor* UWorldUtilLib::Spawn
(
	UWorld* const InWorld, UClass* const InClass, const FTransform& InTransform,
	EMySpawnFlags const InFlags,
       	const FActorSpawnParameters& InSpawnParameters,
       	ELogFlags const InLogFlags
)
{
	M_LOGFUNC_IF_FLAGS(InLogFlags);
	checkf(InWorld, TEXT("UWorld must be valid when calling %s"), TEXT(__FUNCTION__));
	checkf(InClass, TEXT("Class must be valid when calling %s"), TEXT(__FUNCTION__));

	{ // Logging actor info
		bool const bFullActorLog = (InFlags & EMySpawnFlags::FullActorLog) != EMySpawnFlags::None;

		ULogUtilLib::LogNameIfFlagsC(InLogFlags, TEXT("Name"), InSpawnParameters.Name);

		ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("Class"), InClass->GetName());
		ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("Location"), InTransform.GetLocation().ToString());
		ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("Rotation"), InTransform.GetRotation().ToString());

		ULogUtilLib::LogStringIfFlagsC(InLogFlags, TEXT("ObjectFlags"), ULogUtilLib::GetObjectFlagsStringScoped(InSpawnParameters.ObjectFlags));
		ULogUtilLib::LogYesNoIfFlagsC(InLogFlags, TEXT("bNoFail"), InSpawnParameters.bNoFail);

		if(bFullActorLog)
		{
			ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Template"), InSpawnParameters.Template);
			ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Owner"), InSpawnParameters.Owner);
			ULogUtilLib::LogKeyedNameClassSafeC(TEXT("Instigator"), InSpawnParameters.Instigator);
		}
	} // Logging actor info

	AActor* const A = InWorld->SpawnActor(InClass, &InTransform, InSpawnParameters);

	M_LOG_IF_FLAGS(InLogFlags, TEXT("SpawnActor returned"));
	ULogUtilLib::LogObjectSafeIfFlags(InLogFlags, A);

	bool const bAssertIfFail = (InFlags & EMySpawnFlags::AllowFail) == EMySpawnFlags::None;
	if(bAssertIfFail)
	{
		checkf(A, TEXT("UWorld::Spawn must succeed (due to flags)"));
	}

	return A;
}

AActor* UWorldUtilLib::Spawn
( 
	UWorld* const InWorld, UClass* const InClass, const FVector& InLocation, const FRotator& InRotation, 
	EMySpawnFlags const InFlags,
	const FActorSpawnParameters& InSpawnParameters, ELogFlags const InLogFlags
)
{
	checkNoRecursion();
	return Spawn(InWorld, InClass, FTransform{InRotation, InLocation, FVector{1.F,1.F,1.F}}, InFlags, InSpawnParameters, InLogFlags);
}

AActor* UWorldUtilLib::K2SpawnByTransform
( 
	UObject* const InWorldContextObject, UClass* const InClass, const FTransform& InTransform,
	EMySpawnFlags const InFlags,
       	ELogFlags const InLogFlags
)
{
	checkf(GEngine, TEXT("GEngine must be valid when calling %s"), TEXT(__FUNCTION__));
	UWorld* const W = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::Assert);
	return Spawn(W, InClass, InTransform, InFlags, FActorSpawnParameters{}, InLogFlags);
}

AActor* UWorldUtilLib::K2Spawn
(
	UObject* const InWorldContextObject, UClass* const InClass, const FVector& InLocation, const FRotator& InRotation,
	EMySpawnFlags const InFlags,
       	ELogFlags const InLogFlags
)
{
	checkf(GEngine, TEXT("GEngine must be valid when calling %s"), TEXT(__FUNCTION__));
	UWorld* const W = GEngine->GetWorldFromContextObject(InWorldContextObject, EGetWorldErrorMode::Assert);
	return Spawn(W, InClass, InLocation, InRotation, InFlags, FActorSpawnParameters{}, InLogFlags);
}

FString UWorldUtilLib::GetMapName_NoStreamingPrefix(UWorld* const InWorld, ELogFlags const InLogFlags)
{
	check(InWorld);

	FString const MapName = InWorld->GetMapName();
	M_LOG_IF_FLAGS(InLogFlags, TEXT("UWorld::GetMapName() returned \"%s\""), *MapName);

	FString MapName_NoStreamingPrefix = MapName;
	MapName_NoStreamingPrefix.RemoveFromStart(InWorld->StreamingLevelsPrefix);

	M_LOG_IF_FLAGS(InLogFlags, TEXT("MapName(no streaming prefix): \"%s\""), *MapName_NoStreamingPrefix);
	return MapName;
}
