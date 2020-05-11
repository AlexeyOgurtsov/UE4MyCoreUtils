#pragma once

#include "BasicItem.h"
#include "BasicItemValue.generated.h"

UCLASS(BlueprintType)
class UBasicItemValue : public UBasicItem
{
	GENERATED_BODY()

public:
	void Initialize(const FBasicItemInfo& InInfo);

	virtual FBasicItemInfo GetInfo() const override { return Info; }

	virtual FBasicItemSelectionState GetSelection() const override { return Selection; }

	virtual void SetSelectionState(bool bInSelected) override;

private:
	UPROPERTY(BlueprintReadOnly, Category = Item, Meta=(AllowPrivateAccess = true))
	FBasicItemSelectionState Selection;

	UPROPERTY(BlueprintReadOnly, Category = Item, Meta=(AllowPrivateAccess = true))
	FBasicItemInfo Info;
};
