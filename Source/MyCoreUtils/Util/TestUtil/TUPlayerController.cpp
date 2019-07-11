#include "TUPlayerController.h"
#include "TUPawn.h"

#include "Util/Core/LogUtilLib.h"

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
}
void ATUPlayerController::SetupInputComponent()
{
	M_LOGFUNC();
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

void ATUPlayerController::Axis_LookPitchChecked(float const InValue)
{
	if(ShouldProcessGameInput())
	{
		Axis_LookPitch(InValue);
	}
}

void ATUPlayerController::Axis_LookYawChecked(float const InValue)
{
	if(ShouldProcessGameInput())
	{
		Axis_LookYaw(InValue);
	}
}

void ATUPlayerController::Axis_LookPitch(float const InValue)
{
	if(InValue != 0.0F)
	{
		AddPitchInput(InValue * GetWorld()->GetDeltaSeconds() * LOOK_PITCH_SPEED);
	}
}

void ATUPlayerController::Axis_LookYaw(float const InValue)
{
	if(InValue != 0.0F)
	{
		AddYawInput(InValue * GetWorld()->GetDeltaSeconds() * LOOK_YAW_SPEED);
	}
}

void ATUPlayerController::Axis_ForwardChecked(float const InValue)
{
	if(APawn* const P = GetPawnIfShouldLogged(TEXT(__FUNCTION__)))
	{
		Axis_Forward(InValue);
	}
}

void ATUPlayerController::Axis_RightChecked(float const InValue)
{
	if(APawn* const P = GetPawnIfShouldLogged(TEXT(__FUNCTION__)))
	{
		Axis_Right(InValue);
	}
}

void ATUPlayerController::Axis_UpChecked(float const InValue)
{
	if(APawn* const P = GetPawnIfShouldLogged(TEXT(__FUNCTION__)))
	{
		Axis_Up(InValue);
	}
}

void ATUPlayerController::Axis_Forward(float const InValue)
{
	ActionMoveGeneral(GetPawn()->GetActorForwardVector(), InValue);
}

void ATUPlayerController::Axis_Right(float const InValue)
{
	ActionMoveGeneral(GetPawn()->GetActorRightVector(), InValue);
}

void ATUPlayerController::Axis_Up(float const InValue)
{
	ActionMoveGeneral(GetPawn()->GetActorUpVector(), InValue);
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

void ATUPlayerController::ActionMoveGeneral(const FVector& InDirection, const float InAmount)
{
	if(InAmount != 0.0F)
	{
		GetPawn()->AddMovementInput(InDirection, MOVE_AMOUNT_COEFF * InAmount);
	}
}


bool ATUPlayerController::ShouldProcessGameInputLogged(const TCHAR* const InSender) const
{
	bool const bShouldProcess = ShouldProcessGameInput();
	M_LOG_ERROR_IF( ! bShouldProcess, TEXT("Action %s: Skipping processing game input (not Game context!) "), InSender)
	return bShouldProcess;
}

APawn* ATUPlayerController::GetPawnIfShouldLogged(const TCHAR* const InSender) const
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
