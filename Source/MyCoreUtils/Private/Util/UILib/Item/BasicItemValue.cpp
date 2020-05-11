#include "BasicItemValue.h"

void UBasicItemValue::Initialize(const FBasicItemInfo& InInfo)
{
	Info = InInfo;
}

void UBasicItemValue::SetSelectionState(const bool bInSelected) 
{
	Selection.bSelected = bInSelected;
}
