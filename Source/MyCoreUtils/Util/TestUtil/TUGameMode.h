#pragma once

#include "GameFramework/GameModeBase.h"
#include "TUGameMode.generated.h"

UCLASS()
class ATUGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATUGameMode();

	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	/**
	* If true, we log non-periodic big events, like BeginPlay, Possess etc.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Test", Meta=(AllowPrivateAccess = true))
	bool bLogBigEvents = true;
	// ~Logging End
	
	// ~AActor Begin
	virtual void PreInitializeComponents() override;
	virtual void Reset() override;
	// ~AActor End

	// ~AGameMode Begin
	/**
	 * Initialize the game.
	 * The GameMode's InitGame() event is called before any other functions (including PreInitializeComponents() )
	 * and is used by the GameMode to initialize parameters and spawn its helper classes.
	 * @warning: this is called before actors' PreInitializeComponents.
	 */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/**
	 * Initialize the GameState actor with default settings
	 * called during PreInitializeComponents() of the GameMode after a GameState has been spawned
	 * as well as during Reset()
	 */
	virtual void InitGameState() override;

	/**
	 * Overridable function called when resetting level. This is used to reset the game state while staying in the same map
	 * Default implementation calls Reset() on all actors except GameMode and Controllers
	 */
	virtual void ResetLevel() override;

	/**
	 * Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string.
	 * PreLogin is called before Login.  Significant game time may pass before Login is called
	 *
	 * @param	Options					The URL options (e.g. name/spectator) the player has passed
	 * @param	Address					The network address of the player
	 * @param	UniqueId				The unique id the player has passed to the server
	 * @param	ErrorMessage			When set to a non-empty value, the player will be rejected using the error message set
	 */
	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	/**
	 * Called to login new players by creating a player controller, overridable by the game
	 *
	 * Sets up basic properties of the player (name, unique id, registers with backend, etc) and should not be used to do
	 * more complicated game logic.  The player controller is not fully initialized within this function as far as networking is concerned.
	 * Save "game logic" for PostLogin which is called shortly afterward.
	 *
	 * @param NewPlayer pointer to the UPlayer object that represents this player (either local or remote)
	 * @param RemoteRole the remote role this controller has
	 * @param Portal desired portal location specified by the client
	 * @param Options game options passed in by the client at login
	 * @param UniqueId platform specific unique identifier for the logging in player
	 * @param ErrorMessage [out] error message, if any, why this login will be failing
	 *
	 * If login is successful, returns a new PlayerController to associate with this player. Login fails if ErrorMessage string is set.
	 *
	 * @return a new player controller for the logged in player, NULL if login failed for any reason
	 */
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerController. */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// ~AGameMode End
};
