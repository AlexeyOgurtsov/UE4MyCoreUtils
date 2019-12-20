#pragma once

#include "GameFramework/PlayerState.h"
#include "TUPlayerState.generated.h"


UCLASS()
class ATUPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ATUPlayerState();

	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(Bitmask, BitmaskEnum=ETUPCInputDebugFlags), Category = "Log|Test|Debug")
	bool bLogBigEvents = true;
	// ~Logging End

	// ~UObject Begin
	virtual void PostInitProperties() override;
	// ~UObject End

	// ~AActor Begin
	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type InReason) override;
	// ~AActor End
};
