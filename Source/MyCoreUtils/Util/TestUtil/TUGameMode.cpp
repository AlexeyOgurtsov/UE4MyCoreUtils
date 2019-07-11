#include "TUGameMode.h"
#include "TUPawn.h"
#include "TUPlayerController.h"
#include "Util/Core/LogUtilLib.h"

ATUGameMode::ATUGameMode()
{
	DefaultPawnClass = ATUPawn::StaticClass();
	PlayerControllerClass = ATUPlayerController::StaticClass();
}
