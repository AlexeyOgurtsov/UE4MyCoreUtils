#include "ActorSelectorWidgetBase.h"
#include "Util\Core\LogUtilLib.h"

const FActorSelectorWidgetItem FActorSelectorWidgetItem::EMPTY_ITEM
(
	FText::FromString(TEXT("EMPTY")), nullptr
);

UActorSelectorWidgetBase::UActorSelectorWidgetBase() :
	UUserWidget(FObjectInitializer())
{
	
}

void UActorSelectorWidgetBase::SetSelectedIndex(int32 InSelectedIndex)
{
	SelectedIndex = InSelectedIndex;
	OnSetSelectedIndex(InSelectedIndex);
}


const FActorSelectorWidgetItem& UActorSelectorWidgetBase::GetItemByIndex(int32 const InItemIndex) const
{
	if (IsValidItemIndex(InItemIndex))
	{
		return Items[InItemIndex];
	}
	else
	{
		return FActorSelectorWidgetItem::EMPTY_ITEM;
	}
}

const FText& UActorSelectorWidgetBase::GetItemTitleByIndex(int32 const InItemIndex) const
{
	if (IsValidItemIndex(InItemIndex))
	{
		return GetItemByIndex(InItemIndex).Title;
	}
	else
	{
		return UnselectedItemTitle;
	}
}

void UActorSelectorWidgetBase::ClearItems()
{
	Items.Empty();
	OnClearItems();
}

void UActorSelectorWidgetBase::AddItem(const FActorSelectorWidgetItem& InItem)
{
	Items.Add(InItem);
	OnAddItem(InItem);
}

bool UActorSelectorWidgetBase::Initialize()
{
	if( ! Super::Initialize() )
	{
		return false;
	}
	// @TODO
	return true;
}

void UActorSelectorWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	// @TODO
}

void UActorSelectorWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
	// @TODO
}
