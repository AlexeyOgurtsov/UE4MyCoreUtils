#include "ProjectileDemoGameMode.h"
#include "ProjectileDemoPlayerController.h"
#include "ProjectileDemoPawn.h"
#include "ProjectileDemoConfig.h"
#include "Util/Core/LogUtilLib.h"

MyGameModeType::AProjectileDemoGameMode()
{
	DefaultPawnClass = MyPawnType::StaticClass();
	PlayerControllerClass = MyPCType::StaticClass();
}
