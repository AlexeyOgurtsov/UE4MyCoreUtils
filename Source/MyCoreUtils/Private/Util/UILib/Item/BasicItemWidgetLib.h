#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BasicItemWidgetTypes.h"
#include "BasicItemWidgetLib.generated.h"

class UBasicItem;

UCLASS(BlueprintType)
class UBasicItemWidgetLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = BasicItemWidgetLib)
	static void Set_FromBasicItem(const FBasicItemInfoWidgetSet& Info, const UBasicItem* Item);

	UFUNCTION(BlueprintCallable, Category = BasicItemWidgetLib)
	static void SetText_FromBasicItemTitle(UTextBlock* Widget, const UBasicItem* Item);

	UFUNCTION(BlueprintCallable, Category = BasicItemWidgetLib)
	static void SetImage_FromBasicItem(UImage* Image, const UBasicItem* Item);

	UFUNCTION(BlueprintCallable, Category = BasicItemWidgetLib)
	static void SetActiveStyleForItem(const FBasicItemStyleWidgetSet& InWidgetSet, const UBasicItem* Item, const FBasicItemWidgetStyleRules& StyleRules, bool bHovered);

	UFUNCTION(BlueprintCallable, Category = BasicItemWidgetLib)
	static void SetStyleForItem(const FBasicItemStyleWidgetSet& InWidgetSet, const FBasicItemWidgetStyle& Style);

	UFUNCTION(BlueprintPure, Category = BasicItemWidgetLib)
	static FBasicItemWidgetStyle GetActiveStyleForItem(const UBasicItem* Item, const FBasicItemWidgetStyleRules& StyleRules, bool bHovered);
};
