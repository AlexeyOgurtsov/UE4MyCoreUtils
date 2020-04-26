#include "ActorSelectorWidgetBase.h"
#include "Util\Core\LogUtilLib.h"

UActorSelectorWidgetBase::UActorSelectorWidgetBase() :
	UUserWidget(FObjectInitializer())
{
	
}

void UActorSelectorWidgetBase::SetSelectedIndex(int32 InSelectedIndex)
{
	SelectedIndex = InSelectedIndex;
	OnSetSelectedIndex(InSelectedIndex);
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
