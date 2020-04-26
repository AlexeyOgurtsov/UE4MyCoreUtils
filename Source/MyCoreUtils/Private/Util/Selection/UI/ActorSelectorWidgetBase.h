#pragma once

#include "Blueprint/UserWidget.h"
#include "ActorSelectorWidgetBase.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FActorSelectorWidgetItem
{
    GENERATED_BODY()

    const static FActorSelectorWidgetItem EMPTY_ITEM;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
    FText     Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
    const UObject*    AssociatedObject = nullptr;

    FActorSelectorWidgetItem() {}
    FActorSelectorWidgetItem(const FText& InTitle, const UObject* InAssociatedObject)
        : Title(InTitle)
        , AssociatedObject(InAssociatedObject)
    {
    }
};

UCLASS(BlueprintType)
class UActorSelectorWidgetBase : public UUserWidget
{
	GENERATED_BODY()

public:
      UActorSelectorWidgetBase();

      virtual bool Initialize();

      virtual void NativeConstruct() override;
      virtual void NativeDestruct() override;
      
      void SetSelectedIndex(int32 InSelectedIndex);      
      void ClearItems();
      void AddItem(const FActorSelectorWidgetItem& InItem);

protected:
    UFUNCTION(BlueprintPure, Category = Selection)

    // ~Item index helpers Begin
    bool IsValidItemIndex(int32 InIndex) const { return InIndex >=0 && InIndex < Items.Num();  }
    bool IsSelected() const { return IsValidItemIndex(SelectedIndex); }
    // ~Item index helpers End

    // ~Item access helpers Begin
    /**
    * Helper for getting the item by index.
    * If index is wrong (non-selected or out of range), then empty widget item is returned.
    */
    UFUNCTION(BlueprintPure, Category = Selection)
    const FActorSelectorWidgetItem& GetItemByIndex(int32 InItemIndex) const;

    UFUNCTION(BlueprintPure, Category = Selection)
    const FText& GetItemTitleByIndex(int32 InItemIndex) const;
    // ~Item access helpers End

    // ~Primary implementable events Begin
    // This events are typically implemented inside the concrete widget class!
    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnSetSelectedIndex(int32 InSelectedIndex);

    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnClearItems();

    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnAddItem(const FActorSelectorWidgetItem& InItem);
    // ~Primary implementable events End

    UPROPERTY(BlueprintReadOnly, Category = Selection)
    TArray<FActorSelectorWidgetItem> Items;

    UPROPERTY(BlueprintReadOnly, Category = Selection)
    int32 SelectedIndex = -1;

    UPROPERTY(BlueprintReadOnly, Category = Selection)
    FText UnselectedItemTitle = FText::FromString(TEXT("UNSELECTED"));
};
