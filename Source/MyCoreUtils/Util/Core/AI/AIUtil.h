#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Navigation/PathFollowingComponent.h"
#include "AIUtil.generated.h"

UCLASS()
class UAIUtil : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UAIUtil();

	static FString GetPathFollowingRequestResultString(EPathFollowingRequestResult::Type Code);

	static void LogPathFollowingRequestResult(const FString& InKey, const EPathFollowingRequestResult::Type Code);

	static FString GetPathFollowingResultString(EPathFollowingResult::Type Code);

	static void LogPathFollowingResultCode(const FString& InKey, EPathFollowingResult::Type Code);

	static void LogPathFollowingResult(const FString& InKey, const FPathFollowingResult& Result);

	static void LogPathFollowingResultFlags(const FString& InKey, FPathFollowingResultFlags::Type InFlags);

	static FString GetPathFollowingResultFlagsString(FPathFollowingResultFlags::Type InFlags);
};
