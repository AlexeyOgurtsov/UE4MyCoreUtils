#include "TemplGameMode.h"
#include "TemplPlayerController.h"
#include "TemplPawn.h"
#include "TemplConfig.h"
#include "Util/Core/LogUtilLib.h"

MyGameModeType::ATemplGameMode()
{
	DefaultPawnClass = MyPawnType::StaticClass();
	PlayerControllerClass = MyPCType::StaticClass();
}
