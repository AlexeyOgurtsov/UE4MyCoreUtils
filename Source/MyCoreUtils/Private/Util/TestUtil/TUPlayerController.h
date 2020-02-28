#pragma once

#include "GameFramework/PlayerController.h"
#include "Util\Core\Log\MyLoggingTypes.h"
#include "I/ITUController.h"
#include "TUTypes.h"
#include "TUPlayerController.generated.h"

// ~Types begin
UENUM(BlueprintType, Meta=(Bitflags, UseEnumValuesAsMaskValuesInEditor="true"))
enum class ETUPCInputDebugFlags : uint8
{
	None                  = 0               UMETA(Hidden),

	LogMovement           = 1 << 0          UMETA(DisplayName="Log movement"),
	LogLook               = 1 << 1          UMETA(DisplayName="Log look")
};
ENUM_CLASS_FLAGS(ETUPCInputDebugFlags);

USTRUCT(BlueprintType)
struct FTUPlayerControllerConfig
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Debug")
	FTUConfig TUConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(Bitmask, BitmaskEnum=ETUPCInputDebugFlags), Category = "Input|Debug")
	uint8 InputDebugFlags = static_cast<uint8>(ETUPCInputDebugFlags::None);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta=(Bitmask, BitmaskEnum=ETUPCInputDebugFlags), Category = "Log|Test|Debug")
	bool bLogBigEvents = true;
};
// ~Types end

UCLASS()
class ATUPlayerController 
: public APlayerController
, public ITUController
{
	GENERATED_BODY()

public:
	ATUPlayerController();

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
	
	virtual void SetupInputComponent() override;

	// ~Config Begin
	FTUPlayerControllerConfig GetTUConfig() const { return TUConfig; }
	ETUPCInputDebugFlags GetInputDebugFlags() const { return static_cast<ETUPCInputDebugFlags>(TUConfig.InputDebugFlags); }
	bool HasAnyInputDebugFlagsSet(ETUPCInputDebugFlags const InFlagMask) const { return (GetInputDebugFlags() & InFlagMask) != ETUPCInputDebugFlags::None; }
	bool HasAllInputDebugFlagsSet(ETUPCInputDebugFlags const InFlagMask) const { return (GetInputDebugFlags() & InFlagMask) == InFlagMask; }

	UFUNCTION(BlueprintCallable, Category = "Config")
	ETUFlags GetTUFlags() const { return TUConfig.TUConfig.GetFlags(); }

	UFUNCTION(BlueprintCallable, Category = "Config")
	void UnsetTUFlags(ETUFlags const InFlagMask) { TUConfig.TUConfig.UnsetFlags(InFlagMask); } 

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAnyTUFlags(ETUFlags const InFlagMask) const { return TUConfig.TUConfig.HasAnyFlags(InFlagMask); }

	UFUNCTION(BlueprintPure, Category = "Config")
	bool HasAllTUFlags(ETUFlags const InFlagMask) const { return TUConfig.TUConfig.HasAllFlags(InFlagMask); }
	// ~Config End

	/**
	* Sets the new game input enabled state (true - will be processed)
	*/
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetGameInputEnableState(bool bInEnabled);

	UFUNCTION(BlueprintPure, Category = Input)
	bool IsGameInputAllowed() const { return bGameInputAllowed; }

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
	
protected:
	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_LookPitch(APawn* P, float InAmount);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_LookYaw(APawn* P, float InAmount);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_Forward(APawn* P, float InAmount);

	UFUNCTION(Exec, Category = Motions)
	virtual void Axis_Right(APawn* P, float InAmount);

	UFUNCTION(Exec, Category = Motion)
	virtual void Axis_Up(APawn* P, float InAmount);

	UFUNCTION(Exec, Category = Use)
	virtual void Action_Use();

	UFUNCTION(Exec, Category = Use)
	virtual void Action_UseTwo();

	UFUNCTION(Exec, Category = Use)
	virtual void Action_UseThree();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_Fire();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_FireTwo();

	UFUNCTION(Exec, Category = Fire)
	virtual void Action_FireThree();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectZero();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectOne();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectTwo();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectThree();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectFour();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectFive();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectSix();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectSeven();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectEight();

	UFUNCTION(Exec, Category = Custom)
	virtual void Action_SelectNine();

	UFUNCTION(Exec, Category = Menu)
	virtual void Action_OpenGameMenu();

	UFUNCTION(Exec, Category = Menu)
	virtual void Action_CloseGameMenu();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugOne();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugTwo();

	UFUNCTION(Exec, Category = Debug)
	virtual void Action_DebugThree();

	/**
	* Returns true if game input actions are to be processed.
	* @note: overload.
	*/
	virtual bool ShouldProcessGameInput() const;

	virtual void ActionMoveGeneral(APawn* P, const FVector& InDirection, float InAmount);
	virtual void ActionSelectGeneral(int32 InIndex);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config", Meta=(AllowPrivateAccess = true))
	FTUPlayerControllerConfig TUConfig;

	// ~Actions Begin
	bool ShouldProcessGameInputLogged(const TCHAR* InSender) const;
	APawn* GetPawnIfShouldInGameContextLogged(const TCHAR* InSender) const;
	
	void Axis_LookPitchChecked(float InValue);
	void Axis_LookYawChecked(float InValue);
	void LogLookIfShould(const APawn* P, float InAmount);

	void Axis_ForwardChecked(float InValue);
	void Axis_RightChecked(float InValue);
	void Axis_UpChecked(float InValue);

	void Action_UseChecked();
	void Action_UseTwoChecked();
	void Action_UseThreeChecked();

	void Action_FireChecked();
	void Action_FireTwoChecked();
	void Action_FireThreeChecked();

	void Action_SelectZeroChecked();
	void Action_SelectOneChecked();
	void Action_SelectTwoChecked();
	void Action_SelectThreeChecked();
	void Action_SelectFourChecked();
	void Action_SelectFiveChecked();
	void Action_SelectSixChecked();
	void Action_SelectSevenChecked();
	void Action_SelectEightChecked();
	void Action_SelectNineChecked();

	void ActionSelectGeneralChecked(int32 InIndex);
	// ~Actions End

	UPROPERTY(VisibleInstanceOnly, Category = Input)
	bool bGameInputAllowed = true;
};
