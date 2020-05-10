#pragma once

#include "NetUtilsTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Engine/EngineBaseTypes.h"
#include "Misc/StringFormatArg.h"
#include "NetUtils.generated.h"

class UActorComponent;
class APawn;
class ACharacter;
class AController;
class APlayerController;
class AAIController;

UCLASS(BlueprintType)
class UNetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogComponentNetVars))
	static void LogComponentNetVars(const UActorComponent* Component);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars))
	static void LogNetVars(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars_ControllerPart))
	static void LogNetVars_ControllerPart(const AController* Controller);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars_AIControllerPart))
	static void LogNetVars_AIControllerPart(const AAIController* const AIController);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars_PlayerControllerPart))
	static void LogNetVars_PlayerControllerPart(const APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars_PawnPart))
	static void LogNetVars_PawnPart(const APawn* Actor);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=LogNetVars_CharacterPart))
	static void LogNetVars_CharacterPart(const ACharacter* Actor);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=NetLogf))
	static void K2_NetLogf(const AActor* Actor, const FString& Format, const TArray<FString>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	UFUNCTION(BlueprintCallable, Category="Log|Net", Meta=(DisplayName=NetLogString))
	static void K2_NetLogString(const AActor* Actor, const FString& String, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLog(const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogIf(bool bShouldLog, const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLog(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogIf(bool bShouldLog, const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLogError(const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogErrorIf(bool bShouldLog, const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogError(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogErrorIf(bool bShouldLog, const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLogWarn(const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogWarnIf(bool bShouldLog, const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogWarn(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogWarnIf(bool bShouldLog, const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLog(const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLog(const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLogError(const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogErrorIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogError(const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogErrorIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static void NetLogWarn(const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetLogWarnIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogWarn(const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static void NetPrefixedLogWarnIf(bool bShouldLog, const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static FString NetLogFormat(const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static FString NetPrefixedLogFormat(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	static FString NetLogFormat(const UActorComponent* Comp, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static FString NetPrefixedLogFormat(const UActorComponent* Comp, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetLogPrefix(const AActor* Actor, ENetLogFlags LogFlags = ENetLogFlags::Default);


	static FString GetNetModeString(ENetMode NetMode);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetRoleString(ENetRole Role);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetDormancyString(ENetDormancy Dormancy);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetOwnerString(const AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetNetOwnerString(const AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetInstigatorString(const AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetIsReplicatedString(const AActor* Actor);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetComponentIsReplicatedString(const UActorComponent* Actor);

	
	static void AppendNetModeToLogString(FString& S, ENetMode NM);

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendOwnerToLogString(FString& S, const AActor* Actor);	

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendNetOwnerToLogString(FString& S, const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendInstigatorToLogString(FString& S, const AActor* Actor);	

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendIsReplicatedToLogString(FString& S, const AActor* Actor);	

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendComponentIsReplicatedToLogString(FString& S, const UActorComponent* Comp);
};
