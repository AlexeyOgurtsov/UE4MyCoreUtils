#include "TUGameState.h"
#include "Util/Core/LogUtilLib.h"

ATUGameState::ATUGameState()
{
	M_LOGFUNC();
}

// ~AActor Begin
void ATUGameState::PreInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUGameState::Reset()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::Reset();
}
// ~AActor End

void ATUGameState::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUGameState::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
