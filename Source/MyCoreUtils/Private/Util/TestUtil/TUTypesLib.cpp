#include "TUTypesLib.h"
#include "Util\Core\LogUtilLib.h"

FString UTUTypesLib::GetTUFlagsString(ETUFlags InFlags)
{
	if(InFlags == ETUFlags::None)
	{
		return FString(TEXT("None"));
	}

	FString S;
	if((InFlags & ETUFlags::ExtLog) != ETUFlags::None)
	{
		S.Append(TEXT("ExtLog|"));
	}

	checkNoEntry();
	return FString(TEXT("{ShouldNotGetHere}"));
}

void UTUTypesLib::LogTUFlags(ETUFlags InFlags)
{
	ULogUtilLib::LogStringC(TEXT("TUFlag"), GetTUFlagsString(InFlags));
}