#include "TemplGameMode.h"
#include "TemplPlayerController.h"
#include "TemplPawn.h"
#include "Util/Core/LogUtilLib.h"

ATemplGameMode::ATemplGameMode()
{
	DefaultPawnClass = ATemplPawn::StaticClass();
	PlayerControllerClass = ATemplPlayerController::StaticClass();
}
