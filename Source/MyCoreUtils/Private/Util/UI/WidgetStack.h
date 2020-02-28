#pragma once

/**
* Stack of widgets.
*
* Can be in active or inactive state.
* In active state manages stack of widgets so that only top widget is added to the viewport at any time.
* In inactive state none of the widgets are visible.
*/

#include "WidgetStack.generated.h"

class UUserWidget;
class APlayerController;

UCLASS()
class UWidgetStack : public UObject
{
	GENERATED_BODY()

public:
	UWidgetStack();

	/**
	* See class docs.
	*/
	UFUNCTION(BlueprintPure, Category = Activity)
	bool IsActive() const { return bActive; }

	/**
	* Activates the widget stack.
	*/
	UFUNCTION(BlueprintCallable, Category = Activity)
	void Activate();

	/**
	* Deactivates the widget stack.
	*/
	UFUNCTION(BlueprintCallable, Category = Activity)
	void Deactivate();

	/**
	* @returns: nullptr if stack is empty, otherwise widget.
	*/
	UFUNCTION(BlueprintPure)
	UUserWidget* Top() const;

	/**
	* @returns: count of elements in the stack
	*/
	UFUNCTION(BlueprintPure)
	int32 Num() const { return St.Num(); }

	/**
	* @returns: true if contains no elements.
	*/
	UFUNCTION(BlueprintPure)
	bool IsEmpty() const;

	/**
	* Clears the stack.
	*/
	UFUNCTION(BlueprintCallable)
	void Empty();

	/**
	* Pushs widget on top.
	*/
	UFUNCTION(BlueprintCallable)
	void Push(UUserWidget* InWidget);

	/**
	* Pops widget from top.
	* @returns: nullptr if stack is empty, otherwise widget.
	*/
	UFUNCTION(BlueprintCallable)
	UUserWidget* Pop();

	// ~UObject Begin
	virtual void BeginDestroy() override;
	// ~UObject End

protected:

private:
	// ~Widget helpers Begin
	void HideAllWidgets();

	void AddTopWidgetToViewport();
	void RemoveTopWidgetFromViewport();

	void AddTopWidgetToViewport_IfActive();
	void RemoveTopWidgetFromViewport_IfActive();
	// ~Widget helpers End

	// ~Logging helpers Begin
	FString LogPrefix;
	// ~Logging helpers End

	UPROPERTY()
	bool bActive = false;

	// ~Stack Begin
	UUserWidget* DoPop();

	UPROPERTY()
	TArray<UUserWidget*> St;
	// ~Stack End
};