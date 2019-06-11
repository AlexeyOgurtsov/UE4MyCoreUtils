#include "WorldUtilLib.h"
#include "LogUtilLib.h"

#include "Engine/World.h"

FString UWorldUtilLib::GetMapName_NoStreamingPrefix(UWorld* InWorld, ELogFlags InLogFlags)
{
	check(InWorld);

	FString const MapName = InWorld->GetMapName();
	M_LOG_IF_FLAGS(InLogFlags, TEXT("UWorld::GetMapName() returned \"%s\""), *MapName);

	FString MapName_NoStreamingPrefix = MapName;
	MapName_NoStreamingPrefix.RemoveFromStart(InWorld->StreamingLevelsPrefix);

	M_LOG_IF_FLAGS(InLogFlags, TEXT("MapName(no streaming prefix): \"%s\""), *MapName_NoStreamingPrefix);
	return MapName;
}