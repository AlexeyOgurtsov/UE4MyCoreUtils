#pragma once

#include "NetUtilsTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine/EngineTypes.h"
#include "Misc/StringFormatArg.h"
#include "NetUtils.generated.h"

UCLASS(BlueprintType)
class UNetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
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

	static FString NetLogFormat(const AActor* Actor, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);
	static FString NetPrefixedLogFormat(const AActor* Actor, const TCHAR* Prefix, const TCHAR* Format, const TArray<FStringFormatArg>& Args, ENetLogFlags LogFlags = ENetLogFlags::Default);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetLogPrefix(const AActor* Actor, ENetLogFlags LogFlags = ENetLogFlags::Default);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetRoleString(ENetRole Role);

	UFUNCTION(BlueprintPure, Category="Log|Net")
	static FString GetDormancyString(ENetDormancy Dormancy);

	UFUNCTION(BlueprintPure, Category = "Log|Net")
	static FString GetOwnerString(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Log|Net")
	static void AppendOwnerToLogString(FString& S, const AActor* Actor);	
};
