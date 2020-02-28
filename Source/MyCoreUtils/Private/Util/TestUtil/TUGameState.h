#pragma once

#include "GameFramework/GameStateBase.h"
#include "TUGameState.generated.h"

UCLASS()
class ATUGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	ATUGameState();


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
};
