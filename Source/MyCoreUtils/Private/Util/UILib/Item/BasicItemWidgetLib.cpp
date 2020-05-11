#include "BasicItemWidgetLib.h"

#include "BasicItem.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Border.h"

void UBasicItemWidgetLib::Set_FromBasicItem(const FBasicItemInfoWidgetSet& Info, const UBasicItem* Item)
{
	SetText_FromBasicItemTitle(Info.TitleTextBlock, Item);
	SetImage_FromBasicItem(Info.Image, Item);
}

void UBasicItemWidgetLib::SetText_FromBasicItemTitle(UTextBlock* const Widget, const UBasicItem* Item)
{
	Widget->SetText(Item->GetInfo().Title);
}

void UBasicItemWidgetLib::SetImage_FromBasicItem(UImage* Image, const UBasicItem* Item)
{
	Image->SetBrushFromTexture(Item->GetInfo().Image);
}

FBasicItemWidgetStyle UBasicItemWidgetLib::GetActiveStyleForItem(const UBasicItem* const Item, const FBasicItemWidgetStyleRules& StyleRules, const bool bHovered)
{
	const bool bSelected = Item->IsSelected();
	if(bHovered)
	{
		return bSelected ? StyleRules.HoveredSelected : StyleRules.Hovered;
	}
	else
	{
		return bSelected ? StyleRules.Selected : StyleRules.Normal;
	}
}

void UBasicItemWidgetLib::SetActiveStyleForItem(const FBasicItemStyleWidgetSet& WidgetSet, const UBasicItem* Item, const FBasicItemWidgetStyleRules& StyleRules, const bool bHovered)
{
	const FBasicItemWidgetStyle Style = GetActiveStyleForItem(Item, StyleRules, bHovered);
	SetStyleForItem(WidgetSet, Style);
}

void UBasicItemWidgetLib::SetStyleForItem(const FBasicItemStyleWidgetSet& WidgetSet, const FBasicItemWidgetStyle& Style)
{
	if(WidgetSet.Border)
	{
		WidgetSet.Border->BrushColor = Style.BackgroundPanelColor;
	}

	if(WidgetSet.TitleTextBlock)
	{
		WidgetSet.TitleTextBlock->SetColorAndOpacity(Style.TitleColor);
		WidgetSet.TitleTextBlock->SetOpacity(1.0F);
	}
}
