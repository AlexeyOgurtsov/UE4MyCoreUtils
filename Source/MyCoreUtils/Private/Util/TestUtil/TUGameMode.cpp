#include "TUGameMode.h"
#include "TUPawn.h"
#include "TUPlayerController.h"
#include "TUPlayerState.h"
#include "TUGameState.h"
#include "Util/Core/LogUtilLib.h"

ATUGameMode::ATUGameMode()
{
	DefaultPawnClass = ATUPawn::StaticClass();
	PlayerControllerClass = ATUPlayerController::StaticClass();
	PlayerStateClass = ATUPlayerState::StaticClass();
	GameStateClass = ATUGameState::StaticClass();
}

// ~AActor Begin
void ATUGameMode::PreInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUGameMode::Reset()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::Reset();
}
// ~AActor End

void ATUGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("MapName"), MapName);
		ULogUtilLib::LogStringC(TEXT("Options"), Options);
	}
	Super::InitGame(MapName, Options, ErrorMessage);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("ErrorMessage"), ErrorMessage);
	}
}

void ATUGameMode::InitGameState()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::InitGameState();
}

void ATUGameMode::ResetLevel()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::ResetLevel();
}

void ATUGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("Options"), Options);
		ULogUtilLib::LogStringC(TEXT("Address"), Address);
	}
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("ErrorMessage"), ErrorMessage);
	}
}

APlayerController* ATUGameMode::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("Portal"), Portal);
		ULogUtilLib::LogStringC(TEXT("Options"), Options);
	}
	APlayerController* const PC = Super::Login(NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogStringC(TEXT("ErrorMessage"), ErrorMessage);
	}
	return PC;
}

void ATUGameMode::PostLogin(APlayerController* NewPlayer)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	if(bLogBigEvents)
	{
		ULogUtilLib::LogKeyedNameClassSafeC(TEXT("NewPlayer"), NewPlayer);
	}
	Super::PostLogin(NewPlayer);
}

// ~AGameMode End
void ATUGameMode::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUGameMode::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
