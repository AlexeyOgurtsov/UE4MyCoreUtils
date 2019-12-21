#include "TUCharacter.h"
#include "Util/Core/LogUtilLib.h"

ATUCharacter::ATUCharacter()
{
	M_LOGFUNC();
	LogThis();
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
