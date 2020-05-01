#pragma once

/**
* Actor to be used for testing.
*/

#include "GameFramework/Actor.h"
#include "TUTypes.h"
#include "TUActor.generated.h"

UCLASS()
class ATUActor : public AActor
{
	GENERATED_BODY()

public:
	ATUActor();

	virtual void PostLoad() override;

	virtual void BeginPlay() override;
	virtual void EndPlay(EEndPlayReason::Type InReason) override;
	virtual void Tick(float DeltaSeconds) override;

	virtual void PreRegisterAllComponents() override;
	virtual void PostRegisterAllComponents() override;
	virtual void PostActorCreated() override;

	/**
	* When placed in editor or spawned.
	*/
	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void PreInitializeComponents() override;
	virtual void PostInitializeComponents() override;

	// ~Config Begin
	UFUNCTION(BlueprintPure, Category = "Config")
	ETUFlags GetTUFlags() const { return TUConfig.GetFlags(); }

	/**
	* Sets flags (and KEEPS old!)
	*/
	UFUNCTION(BlueprintCallable, Category = "Config")
	void SetTUFlags(ETUFlags InFlagMask);

	/**
	* Unsets the given set of flags.
	*/
	UFUNCTION(BlueprintCallable, Category = "Config")
	void UnsetTUFlags(ETUFlags InFlagMask);

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAnyTUFlags(ETUFlags InFlagMask) const;

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAllTUFlags(ETUFlags InFlagMask) const;

	UFUNCTION(BlueprintCallable)
	void LogTUFlags();
	// ~Config End

	// ~Log Begin
	UFUNCTION(BlueprintCallable)
	void LogThis();

	UFUNCTION(BlueprintCallable)
	void LogThisIf(bool bInShouldLog);
	// ~Log End

private:
	void RenderBoundsIfShould();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Meta=(AllowPrivateAccess = true))
	FTUConfig TUConfig;	
};
