#pragma once

#include "GameFramework/Character.h"
#include "TUCharacter.generated.h"

UCLASS()
class ATUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATUCharacter();

	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	/**
	* If true, we log non-periodic big events, like BeginPlay, Possess etc.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Test", Meta=(AllowPrivateAccess = true))
	bool bLogBigEvents = true;
	// ~Logging End
};
