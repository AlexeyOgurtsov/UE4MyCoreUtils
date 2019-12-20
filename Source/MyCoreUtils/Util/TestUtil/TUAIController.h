#pragma once

#include "AIController.h"
#include "Util/Core/Log/MyLoggingTypes.h"
#include "I/ITUController.h"
#include "TUTypes.h"
#include "TUAIController.generated.h"

// ~Types begin
UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class ETUAIControllerInputDebugFlags : uint8
{
	None                  = 0               UMETA(Hidden),

	LogMovement           = 1 << 0          UMETA(DisplayName="Log movement"),
	LogLook               = 1 << 1          UMETA(DisplayName="Log look")
};
ENUM_CLASS_FLAGS(ETUAIControllerInputDebugFlags);

USTRUCT(BlueprintType)
struct FTUAIControllerConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	FTUConfig TUConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(Bitmask, BitmaskEnum=ETUAIControllerInputDebugFlags), Category = "Log|Test|Debug")
	bool bLogBigEvents = true;
};
// ~Types end

UCLASS()
class ATUAIController 
: public AAIController
, public ITUController
{
	GENERATED_BODY()

public:
	ATUAIController();

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
	
	// ~AController Begin
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
	virtual void SetPawn(APawn* InPawn) override;
	// ~AController End

	// ~Logging Begin
	virtual void LogThis();
	void LogThisIf(bool bInShouldLog);
	// ~Logging End

	// ~ITUController Begin
	virtual void PawnBeginPlayEnded_Implementation() override;
	// ~ITUController End

	// ~Config Begin
	FTUAIControllerConfig GetTUConfig() const { return TUConfig; }

	UFUNCTION(BlueprintCallable, Category = "Config")
	ETUFlags GetTUFlags() const { return TUConfig.TUConfig.GetFlags(); }

	UFUNCTION(BlueprintCallable, Category = "Config")
	void UnsetTUFlags(ETUFlags const InFlagMask) { TUConfig.TUConfig.UnsetFlags(InFlagMask); } 

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAnyTUFlags(ETUFlags const InFlagMask) const { return TUConfig.TUConfig.HasAnyFlags(InFlagMask); }

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAllTUFlags(ETUFlags const InFlagMask) const { return TUConfig.TUConfig.HasAllFlags(InFlagMask); }
	// ~Config End

	// ~Access helpers Begin
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetTUPawn() const;

	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetMyTUPawnLogged(ELogFlags InLogFlags = ELogFlags::None) const;

	/**
	* Checks that the given pawn NOT null.
	*/
	UFUNCTION(BlueprintPure, Category = Pawn)
	ATUPawn* GetMyTUPawnChecked() const;
	// ~Access helpers End

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Meta=(AllowPrivateAccess = true))
	FTUAIControllerConfig TUConfig;
};
