#include "TUPlayerController.h"
#include "TUPawn.h"

#include "Util/Core/LogUtilLib.h"

#include "GameFramework/PawnMovementComponent.h" // For casts
#include "Engine/World.h" // UWorld::GetDeltaSeconds()

namespace
{
	constexpr int32 NUM_SELECT_ACTIONS = 10;


	/**
	* WARNING! Typically this coeff is to be ONE always, the movement speed is to be configurated inside the movement component!
	*/
	constexpr float MOVE_AMOUNT_COEFF = 1.0F;

	constexpr float LOOK_YAW_SPEED = 5.0F;
	constexpr float LOOK_PITCH_SPEED = 5.0F;
} // anonymous

ATUPlayerController::ATUPlayerController()
{
	M_LOGFUNC();
	LogThis();
}

void ATUPlayerController::PostInitProperties()
{
	Super::PostInitProperties();

	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
}

void ATUPlayerController::PreRegisterAllComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PreRegisterAllComponents();
}

void ATUPlayerController::PostRegisterAllComponents() 
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PostRegisterAllComponents();
}

void ATUPlayerController::PreInitializeComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUPlayerController::PostInitializeComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PostInitializeComponents();
}

void ATUPlayerController::BeginPlay()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::BeginPlay();
}

void ATUPlayerController::EndPlay(EEndPlayReason::Type InReason)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::EndPlay(InReason);
}

void ATUPlayerController::OnPossess(APawn* InPawn)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (BEFORE Super)"), GetPawn());
	Super::OnPossess(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (AFTER Super)"), GetPawn());
}

void ATUPlayerController::OnUnPossess()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::OnUnPossess();
}

void ATUPlayerController::SetPawn(APawn* InPawn)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (BEFORE Super)"), GetPawn());
	Super::SetPawn(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (AFTER Super)"), GetPawn());
}

void ATUPlayerController::PawnBeginPlayEnded_Implementation()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
}

void ATUPlayerController::SetupInputComponent()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);

	Super::SetupInputComponent();
	checkf(InputComponent, TEXT("Input component must be created (did you forget Super-call?)"));

	InputComponent->BindAxis(TEXT("Forward"), this, &ATUPlayerController::Axis_ForwardChecked);
	InputComponent->BindAxis(TEXT("Right"), this, &ATUPlayerController::Axis_RightChecked);
	InputComponent->BindAxis(TEXT("Up"), this, &ATUPlayerController::Axis_UpChecked);

	InputComponent->BindAxis(TEXT("LookPitch"), this, &ATUPlayerController::Axis_LookPitchChecked);
	InputComponent->BindAxis(TEXT("LookYaw"), this, &ATUPlayerController::Axis_LookYawChecked);

	InputComponent->BindAction(TEXT("Use"), IE_Pressed, this, &ATUPlayerController::Action_UseChecked);
	InputComponent->BindAction(TEXT("UseTwo"), IE_Pressed, this, &ATUPlayerController::Action_UseTwoChecked);
	InputComponent->BindAction(TEXT("UseThree"), IE_Pressed, this, &ATUPlayerController::Action_UseThreeChecked);

	InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATUPlayerController::Action_FireChecked);
	InputComponent->BindAction(TEXT("FireTwo"), IE_Pressed, this, &ATUPlayerController::Action_FireTwoChecked);
	InputComponent->BindAction(TEXT("FireThree"), IE_Pressed, this, &ATUPlayerController::Action_FireThreeChecked);

	InputComponent->BindAction(TEXT("SelectZero"), IE_Pressed, this, &ATUPlayerController::Action_SelectZeroChecked);
	InputComponent->BindAction(TEXT("SelectOne"), IE_Pressed, this, &ATUPlayerController::Action_SelectOneChecked);
	InputComponent->BindAction(TEXT("SelectTwo"), IE_Pressed, this, &ATUPlayerController::Action_SelectTwoChecked);
	InputComponent->BindAction(TEXT("SelectThree"), IE_Pressed, this, &ATUPlayerController::Action_SelectThreeChecked);
	InputComponent->BindAction(TEXT("SelectFour"), IE_Pressed, this, &ATUPlayerController::Action_SelectFourChecked);
	InputComponent->BindAction(TEXT("SelectFive"), IE_Pressed, this, &ATUPlayerController::Action_SelectFiveChecked);
	InputComponent->BindAction(TEXT("SelectSix"), IE_Pressed, this, &ATUPlayerController::Action_SelectSixChecked);
	InputComponent->BindAction(TEXT("SelectSeven"), IE_Pressed, this, &ATUPlayerController::Action_SelectSevenChecked);
	InputComponent->BindAction(TEXT("SelectEight"), IE_Pressed, this, &ATUPlayerController::Action_SelectEightChecked);
	InputComponent->BindAction(TEXT("SelectNine"), IE_Pressed, this, &ATUPlayerController::Action_SelectNineChecked);

	InputComponent->BindAction(TEXT("OpenGameMenu"), IE_Pressed, this, &ATUPlayerController::Action_OpenGameMenu);
	InputComponent->BindAction(TEXT("CloseGameMenu"), IE_Pressed, this, &ATUPlayerController::Action_CloseGameMenu);

	InputComponent->BindAction(TEXT("DebugOne"), IE_Pressed, this, &ATUPlayerController::Action_DebugOne);
	InputComponent->BindAction(TEXT("DebugTwo"), IE_Pressed, this, &ATUPlayerController::Action_DebugTwo);
	InputComponent->BindAction(TEXT("DebugThree"), IE_Pressed, this, &ATUPlayerController::Action_DebugThree);
}

void ATUPlayerController::SetGameInputEnableState(bool bInEnabled)
{
	bGameInputAllowed = bInEnabled;
	if(bInEnabled)
	{
		M_LOG(TEXT("Game input enabled"));
	}
	else
	{
		M_LOG(TEXT("Game input disabled"));
	}
}

void ATUPlayerController::Axis_LookPitchChecked(float const InAmount)
{
	if(APawn* const P = GetPawnIfShouldInGameContextLogged(TEXT(__FUNCTION__)))
	{
		Axis_LookPitch(P, InAmount);
	}
}

void ATUPlayerController::Axis_LookYawChecked(float const InAmount)
{
	if(APawn* const P = GetPawnIfShouldInGameContextLogged(TEXT(__FUNCTION__)))
	{
		Axis_LookYaw(P, InAmount);
	}
}

void ATUPlayerController::Axis_LookPitch(APawn* const P, float const InAmount)
{
	checkf(P, TEXT("When calling %s pawn must be valid non-NULL pointer"), TEXT(__FUNCTION__));
	if(InAmount != 0.0F)
	{
		LogLookIfShould(P, InAmount);
		AddPitchInput(InAmount * GetWorld()->GetDeltaSeconds() * LOOK_PITCH_SPEED);
	}
}


void ATUPlayerController::Axis_LookYaw(APawn* const P, float const InAmount)
{
	checkf(P, TEXT("When calling %s pawn must be valid non-NULL pointer"), TEXT(__FUNCTION__));
	if(InAmount != 0.0F)
	{
		LogLookIfShould(P, InAmount);
		AddYawInput(InAmount * GetWorld()->GetDeltaSeconds() * LOOK_YAW_SPEED);
	}
}

void ATUPlayerController::LogLookIfShould(const APawn* const P, float InAmount)
{
	M_LOG_IF(HasAnyInputDebugFlagsSet(ETUPCInputDebugFlags::LogLook), TEXT("LookPitch action: Amount=%f (MovementComponent={%s})"), InAmount, *ULogUtilLib::GetNameAndClassSafe(P->GetMovementComponent()));
}

void ATUPlayerController::Axis_ForwardChecked(float const InAmount)
{
	if(APawn* const P = GetPawnIfShouldInGameContextLogged(TEXT(__FUNCTION__)))
	{
		Axis_Forward(P, InAmount);
	}
}

void ATUPlayerController::Axis_RightChecked(float const InAmount)
{
	if(APawn* const P = GetPawnIfShouldInGameContextLogged(TEXT(__FUNCTION__)))
	{
		Axis_Right(P, InAmount);
	}
}

void ATUPlayerController::Axis_UpChecked(float const InAmount)
{
	if(APawn* const P = GetPawnIfShouldInGameContextLogged(TEXT(__FUNCTION__)))
	{
		Axis_Up(P, InAmount);
	}
}

void ATUPlayerController::Axis_Forward(APawn* const P, float const InAmount)
{
	checkf(P, TEXT("When calling %s pawn must be non-NULL pointer"), TEXT(__FUNCTION__));
	ActionMoveGeneral(P, P->GetActorForwardVector(), InAmount);
}

void ATUPlayerController::Axis_Right(APawn* const P, float const InAmount)
{
	checkf(P, TEXT("When calling %s pawn must be non-NULL pointer"), TEXT(__FUNCTION__));
	ActionMoveGeneral(P, P->GetActorRightVector(), InAmount);
}

void ATUPlayerController::Axis_Up(APawn* const P, float const InAmount)
{
	checkf(P, TEXT("When calling %s pawn must be non-NULL pointer"), TEXT(__FUNCTION__));
	ActionMoveGeneral(P, P->GetActorUpVector(), InAmount);
}

void ATUPlayerController::Action_UseChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_Use();
	}
}

void ATUPlayerController::Action_UseTwoChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_UseTwo();
	}
}

void ATUPlayerController::Action_UseThreeChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_UseThree();
	}
}

void ATUPlayerController::Action_Use()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_UseTwo()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_UseThree()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_FireChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_Fire();
	}
}

void ATUPlayerController::Action_FireTwoChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_FireTwo();
	}
}

void ATUPlayerController::Action_FireThreeChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_FireThree();
	}
}

void ATUPlayerController::Action_Fire()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}


void ATUPlayerController::Action_FireTwo()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_FireThree()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_SelectZeroChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectZero();
	}
}

void ATUPlayerController::Action_SelectOneChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectOne();
	}
}

void ATUPlayerController::Action_SelectTwoChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectTwo();
	}
}

void ATUPlayerController::Action_SelectThreeChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectThree();
	}
}

void ATUPlayerController::Action_SelectFourChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectFour();
	}
}

void ATUPlayerController::Action_SelectFiveChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectFive();
	}
}

void ATUPlayerController::Action_SelectSixChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectSix();
	}
}

void ATUPlayerController::Action_SelectSevenChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectSeven();
	}
}

void ATUPlayerController::Action_SelectEightChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectEight();
	}
}

void ATUPlayerController::Action_SelectNineChecked()
{
	if(ShouldProcessGameInputLogged(TEXT(__FUNCTION__)))
	{
		Action_SelectNine();
	}
}

void ATUPlayerController::Action_SelectZero()
{
	ActionSelectGeneral(0);
}

void ATUPlayerController::Action_SelectOne()
{
	ActionSelectGeneral(1);
}

void ATUPlayerController::Action_SelectTwo()
{
	ActionSelectGeneral(2);
}

void ATUPlayerController::Action_SelectThree()
{
	ActionSelectGeneral(3);
}

void ATUPlayerController::Action_SelectFour()
{
	ActionSelectGeneral(4);
}

void ATUPlayerController::Action_SelectFive()
{
	ActionSelectGeneral(5);
}

void ATUPlayerController::Action_SelectSix()
{
	ActionSelectGeneral(6);
}

void ATUPlayerController::Action_SelectSeven()
{
	ActionSelectGeneral(7);
}

void ATUPlayerController::Action_SelectEight()
{
	ActionSelectGeneral(8);
}

void ATUPlayerController::Action_SelectNine()
{
	ActionSelectGeneral(9);
}

void ATUPlayerController::Action_OpenGameMenu()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_CloseGameMenu()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_DebugOne()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_DebugTwo()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::Action_DebugThree()
{
	M_LOG(TEXT("Action %s: skipping (empty)"), TEXT(__FUNCTION__));
}

void ATUPlayerController::ActionSelectGeneralChecked(const int32 InIndex)
{
	M_LOGFUNC();

	checkf(InIndex >= 0, TEXT("Action index out of range: %d"), InIndex);
	checkf(InIndex < NUM_SELECT_ACTIONS, TEXT("Action index of out range: %d"), InIndex);

	ActionSelectGeneral(InIndex);	
}

void ATUPlayerController::ActionSelectGeneral(const int32 InIndex)
{
	M_LOG(TEXT("Select action N %d: skipping (empty)"), InIndex);
}

void ATUPlayerController::ActionMoveGeneral(APawn* const P, const FVector& InDirection, const float InAmount)
{
	checkf(P, TEXT("When calling %s Pawn must be valid non-NULL pointer"), TEXT(__FUNCTION__));

	// For debug:
	if(InAmount != 0.0F)
	{
		M_LOG_IF(HasAnyInputDebugFlagsSet(ETUPCInputDebugFlags::LogMovement), TEXT("Movement action: Direction=%s Amount=%f (Movement={%s})"), *InDirection.ToString(), InAmount, *ULogUtilLib::GetNameAndClassSafe(P->GetMovementComponent()));

		M_LOG_WARN_IF(GetPawn()->GetMovementComponent() == nullptr, TEXT("Movement component is nullptr for controlled pawn"));
		P->AddMovementInput(InDirection, MOVE_AMOUNT_COEFF * InAmount);
	}
}

bool ATUPlayerController::ShouldProcessGameInputLogged(const TCHAR* const InSender) const
{
	bool const bShouldProcess = ShouldProcessGameInput();
	M_LOG_ERROR_IF( ! bShouldProcess, TEXT("Action %s: Skipping processing game input (not Game context!) "), InSender)
	return bShouldProcess;
}

APawn* ATUPlayerController::GetPawnIfShouldInGameContextLogged(const TCHAR* const InSender) const
{
	if( ! ShouldProcessGameInputLogged(InSender) )
	{
		return false;
	}
	M_LOG_ERROR_IF(GetPawn() == nullptr, TEXT("Action %s: Unable to get pawn (GetPawn() returned nullptr)"), InSender);
	return GetPawn();
}

bool ATUPlayerController::ShouldProcessGameInput() const
{
	return bGameInputAllowed && ! bCinematicMode;
}

ATUPawn* ATUPlayerController::GetTUPawn() const
{
	return Cast<ATUPawn>(GetPawn());
}

ATUPawn* ATUPlayerController::GetMyTUPawnLogged(ELogFlags InLogFlags) const
{
	ATUPawn* const P = GetTUPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUPawn() returned NULL"));
	}
	return P;
}

ATUPawn* ATUPlayerController::GetMyTUPawnChecked() const
{
	ATUPawn* const P = GetTUPawn();
	checkf(P, TEXT("GetTUPawn() must return non-NULL pawn!"));
	return P;
}

void ATUPlayerController::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUPlayerController::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
