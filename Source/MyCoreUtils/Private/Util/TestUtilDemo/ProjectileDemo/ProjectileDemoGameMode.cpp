#include "ProjectileDemoGameMode.h"
#include "ProjectileDemoPlayerController.h"
#include "ProjectileDemoPawn.h"
#include "ProjectileDemoConfig.h"
#include "Util/Core/LogUtilLib.h"

MyProjectileDemoGameModeType::AProjectileDemoGameMode()
{
	DefaultPawnClass = MyProjectileDemoPawnType::StaticClass();
	PlayerControllerClass = MyProjectileDemoPCType::StaticClass();
}
