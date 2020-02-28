#include "TypeUtilLib.h"
#include "UObject/Package.h"
#include "LogUtilLib.h"

int32 UTypeUtilLib::FindEnumIndexByName(const FString& InEnumName, const FString& InString)
{
	UEnum* C = FindObject<UEnum>(ANY_PACKAGE, *InEnumName, /*ExactClass*/true);
	if(C == nullptr)
	{
		return INDEX_NONE;
	}
	else
	{
		return C->GetIndexByName(FName(*InString, FNAME_Find));
	}
}

int32 UTypeUtilLib::FindEnumIndexByNameChecked(const FString& InEnumName, const FString& InString)
{
	int32 const LiteralIndex = FindEnumIndexByName(InEnumName, InString);
	checkf(LiteralIndex, TEXT("%s failed, maybe try unchecked version instead"), __FUNCTION__);
	return LiteralIndex;
}