#pragma once

#include "BasicItemTypes.h"
#include "BasicItem.generated.h"

UCLASS(Abstract)
class UBasicItem : public UObject
{
	GENERATED_BODY()

public:
	// ~Main Interface Begin
	UFUNCTION(BlueprintPure, Category=Selection)
	virtual FBasicItemSelectionState GetSelection() const PURE_VIRTUAL(UBasicItem::GetSelection, return FBasicItemSelectionState{}; );

	UFUNCTION(BlueprintPure, Category=Info)
	virtual FBasicItemInfo GetInfo() const PURE_VIRTUAL(UBasicItem::GetInfo, return FBasicItemInfo{}; );

	UFUNCTION(BlueprintCallable, Category=Info)
	virtual void SetSelectionState(bool bInSelected) PURE_VIRTUAL(UBasicItem::SetSelectionState, );
	// ~Main Interface End

	// ~Helpers Begin
	UFUNCTION(BlueprintPure, Category=Info)
	bool IsSelected() const { return GetSelection().bSelected; }
	// ~Helpers End
};
