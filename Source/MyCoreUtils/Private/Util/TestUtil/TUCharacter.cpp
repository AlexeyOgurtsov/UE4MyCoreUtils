#include "TUCharacter.h"

#include "GameFramework/PlayerController.h"
#include "I/ITUController.h"
#include "Util/Core/LogUtilLib.h"

ATUCharacter::ATUCharacter()
{
	M_LOGFUNC();
	LogThis();
}

void ATUCharacter::OnController_Axis_LookPitch_Implementation(float InAmount)
{
	GetTUControllerChecked()->Default_Axis_LookPitch(this, InAmount);
}

void ATUCharacter::OnController_Axis_LookYaw_Implementation(float InAmount)
{
	GetTUControllerChecked()->Default_Axis_LookYaw(this, InAmount);
}

void ATUCharacter::OnController_Axis_Forward_Implementation(float InAmount)
{
	GetTUControllerChecked()->Default_Axis_Forward(this, InAmount);
}

void ATUCharacter::OnController_Axis_Right_Implementation(float InAmount)
{
	GetTUControllerChecked()->Default_Axis_Right(this, InAmount);
}

void ATUCharacter::OnController_Axis_Up_Implementation(float InAmount)
{
	GetTUControllerChecked()->Default_Axis_Up(this, InAmount);
}

void ATUCharacter::OnController_Action_Use_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_UseTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_UseThree_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_Fire_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_FireTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_FireThree_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectZero_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectOne_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectThree_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectFour_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectFive_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectSix_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectSeven_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectEight_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_SelectNine_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_OpenGameMenu_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_CloseGameMenu_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_DebugOne_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_DebugTwo_Implementation()
{
	// Nothing is done here yet
}

void ATUCharacter::OnController_Action_DebugThree_Implementation()
{
	// Nothing is done here yet
}

TScriptInterface<ITUController> ATUCharacter::K2GetTUController() const
{
	return TScriptInterface<ITUController>(GetController());
}

TScriptInterface<ITUController> ATUCharacter::K2GetTUControllerLogged(ELogFlags InLogFlags) const
{
	TScriptInterface<ITUController> const C = K2GetTUController();
	if( ! C )
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

TScriptInterface<ITUController> ATUCharacter::K2GetTUControllerChecked() const
{
	TScriptInterface<ITUController> const C = K2GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

ITUController* ATUCharacter::GetTUController() const
{
	return Cast<ITUController>(GetController());
}

ITUController* ATUCharacter::GetTUControllerLogged(ELogFlags InLogFlags) const
{
	ITUController* const C = GetTUController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUController() returned NULL"));
	}
	return C;
}

ITUController* ATUCharacter::GetTUControllerChecked() const
{
	ITUController* const C = GetTUController();	
	checkf(C, TEXT("GetTUController() must return non-NULL pawn!"));
	return C;
}

AController* ATUCharacter::GetControllerLogged(ELogFlags InLogFlags) const
{
	AController* const C = GetController();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetController() returned NULL"));
	}
	return C;
}

AController* ATUCharacter::GetControllerChecked() const
{
	AController* const C = GetController();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}

APlayerController* ATUCharacter::GetPCLogged(ELogFlags InLogFlags) const
{
	APlayerController* const C = GetPC();
	if(C == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetPC() returned NULL"));
	}
	return C;
}

APlayerController* ATUCharacter::GetPC() const
{
	return Cast<APlayerController>(GetController());
}

APlayerController* ATUCharacter::GetPCChecked() const
{
	APlayerController* const C = GetPC();	
	checkf(C, TEXT("GetController() must return non-NULL pawn!"));
	return C;
}
void ATUCharacter::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUCharacter::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
