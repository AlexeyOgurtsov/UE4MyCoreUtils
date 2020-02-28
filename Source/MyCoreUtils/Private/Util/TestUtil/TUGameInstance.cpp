#include "TUGameInstance.h"
#include "Util/Core/LogUtilLib.h"

void UTUGameInstance::OnStart()
{
	M_LOGFUNC_IF(bLogBigEvents);
	LogThisIf(bLogBigEvents);
	Super::OnStart();
}

void UTUGameInstance::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void UTUGameInstance::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
