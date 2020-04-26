#pragma once

#include "Blueprint/UserWidget.h"
#include "ActorSelectorWidgetBase.generated.h"

class AActor;

USTRUCT(BlueprintType)
struct FActorSelectorWidgetItem
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
    FString     Title;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Selection)
    const UObject*    AssociatedObject = nullptr;

    FActorSelectorWidgetItem() {}
    FActorSelectorWidgetItem(const FString& InTitle, const UObject* InAssociatedObject) 
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
    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnSetSelectedIndex(int32 InSelectedIndex);

    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnClearItems();

    UFUNCTION(BlueprintImplementableEvent, Category = Selection)
    void OnAddItem(const FActorSelectorWidgetItem& InItem);

    UPROPERTY(BlueprintReadOnly, Category = Selection)
    TArray<FActorSelectorWidgetItem> Items;

    UPROPERTY(BlueprintReadOnly, Category = Selection)
    int32 SelectedIndex = 0;
};
