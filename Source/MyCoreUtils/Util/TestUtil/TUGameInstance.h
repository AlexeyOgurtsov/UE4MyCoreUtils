#pragma once

#include "Engine/GameInstance.h"
#include "TUGameInstance.generated.h"

UCLASS()
class UTUGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);

	/**
	* If true, we log non-periodic big events, like BeginPlay, Possess etc.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug|Test", Meta=(AllowPrivateAccess = true))
	bool bLogBigEvents = true;
	// ~Logging End
	
	// ~UGameInstance Begin
	virtual void OnStart() override;
	// ~UGameInstance End
};
