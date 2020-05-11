#pragma once

#include "BasicItemTypes.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FBasicItemSelectionState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	uint32 bSelected : 1;

	FBasicItemSelectionState()
	{
		bSelected = 0;
	}
};

USTRUCT(BlueprintType)
struct FBasicItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	FText Title;

	/**
	* Image DO can be nullptr.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Item")
	UTexture2D* Image = nullptr;

	FBasicItemInfo()
	{ }

	FBasicItemInfo(const FText& InTitle, UTexture2D* const InImage)
	: Title (InTitle)
	, Image (InImage)
	{ }
};
