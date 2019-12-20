#include "TUPlayerState.h"
#include "Util/Core/LogUtilLib.h"

ATUPlayerState::ATUPlayerState()
{
	M_LOGFUNC();
	LogThis();
}

void ATUPlayerState::PostInitProperties()
{
	Super::PostInitProperties();

	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
}

void ATUPlayerState::PreRegisterAllComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreRegisterAllComponents();
}

void ATUPlayerState::PostRegisterAllComponents() 
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PostRegisterAllComponents();
}

void ATUPlayerState::PreInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUPlayerState::PostInitializeComponents()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::PostInitializeComponents();
}

void ATUPlayerState::BeginPlay()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::BeginPlay();
}

void ATUPlayerState::EndPlay(EEndPlayReason::Type InReason)
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::EndPlay(InReason);
}

void ATUPlayerState::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUPlayerState::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
