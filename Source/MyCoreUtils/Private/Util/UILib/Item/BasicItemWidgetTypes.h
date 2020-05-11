#pragma once

#include "Math/Color.h"
#include "BasicItemWidgetTypes.generated.h"

class UBorder;
class UTextBlock;
class UImage;

/**
* Declares set of widgets used when styling.
*/
USTRUCT(BlueprintType)
struct FBasicItemStyleWidgetSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	UBorder* Border = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	UTextBlock* TitleTextBlock = nullptr;

	FBasicItemStyleWidgetSet()
	{ }

	FBasicItemStyleWidgetSet(UBorder* const InBorder, UTextBlock* const InTitleTextBlock)
	: Border(InBorder)
	, TitleTextBlock(InTitleTextBlock)
	{ }
};

/**
* Set of widget variables related to the Info part of the item.
*/
USTRUCT(BlueprintType)
struct FBasicItemInfoWidgetSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	UTextBlock* TitleTextBlock = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	UImage* Image = nullptr;

	FBasicItemInfoWidgetSet()
	{ }

	FBasicItemInfoWidgetSet(UTextBlock* const InTitleTextBlock, UImage* const InImage)
	: TitleTextBlock(InTitleTextBlock)
	, Image(InImage)
	{ }
};

/**
* Entire set of all widget variables, used inside the basic item widget.
*/
USTRUCT(BlueprintType)
struct FBasicItemWidgetSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemStyleWidgetSet Style;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemInfoWidgetSet Info;

	FBasicItemWidgetSet()
	{ }

	FBasicItemWidgetSet(const FBasicItemStyleWidgetSet& InStyle, const FBasicItemInfoWidgetSet& InInfo)
	: Style(InStyle)
	, Info(InInfo)
	{ }

	FBasicItemWidgetSet(UBorder* const InBorder, UTextBlock* const InTitleTextBlock, UImage* const InImage)
	: Style (FBasicItemStyleWidgetSet(InBorder, InTitleTextBlock))
	, Info (FBasicItemInfoWidgetSet(InTitleTextBlock, InImage))
	{ }
};


USTRUCT(BlueprintType)
struct FBasicItemWidgetStyle
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FLinearColor TitleColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FLinearColor BackgroundPanelColor;
};

/**
* Set of styles for each state of the widget.
*/
USTRUCT(BlueprintType)
struct FBasicItemWidgetStyleRules
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemWidgetStyle Normal;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemWidgetStyle Selected;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemWidgetStyle Hovered;	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Style)
	FBasicItemWidgetStyle HoveredSelected;	
};
