#pragma once

#include "Components/ActorComponent.h"
#include "UObject/ScriptInterface.h"
#include "ActorSelectorWidgetBase.h"
#include "ActorSelectorUIComponent.generated.h"

class IActorSelector;
class UActorSelectorWidgetBase;

UCLASS()
class UActorSelectorUIComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Widget)
	TSubclassOf<UActorSelectorWidgetBase> WidgetClass;

public:
	UActorSelectorUIComponent();

	virtual void BeginPlay() override;

	void InitAtControllerBeginPlay(const TScriptInterface<IActorSelector>& InActorSelector);

	void SetActorSelector(const TScriptInterface<IActorSelector>& InActorSelector);
	void UpdateUI();

private:
	FActorSelectorWidgetItem ActorToItem(const AActor* InActor) const;

	bool InitWidget();

	UPROPERTY()
	UActorSelectorWidgetBase* Widget = nullptr;

	UPROPERTY()
	TScriptInterface<IActorSelector> ActorSelector;
};
