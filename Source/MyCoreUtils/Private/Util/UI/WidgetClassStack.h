#pragma once

/**
* Widget class stack.
*
* Can be in active or inactive state.
* In active state manages stack of widgets so that only top widget is added to the viewport at any time.
* In inactive state none of the widgets are visible.
*
* In comparison with WidgetStack automatically creates the widgets;
*/

#include "WidgetClassStackLib.h"
#include "WidgetClassStack.generated.h"

class UUserWidget;
class APlayerController;

/**
* Element for internal implementation of the UWidgetClassStack.
* Should NOT be used outside of the UWidgetClassStack implementation.
*/
USTRUCT()
struct FWidgetClassStack_ImplElem
{
	GENERATED_BODY()

	UPROPERTY()
	FWidgetClassStackElement CreatorElement;

	UPROPERTY()
	UUserWidget* Widget = nullptr;

	bool IsWidgetCreated() const;

	FWidgetClassStack_ImplElem();
	FWidgetClassStack_ImplElem(const FWidgetClassStackElement& InCreatorElement);
};

UCLASS(BlueprintType)
class UWidgetClassStack : public UObject
{
	GENERATED_BODY()

public:
	UWidgetClassStack();

	// ~ Creation Begin
	UFUNCTION(BlueprintCallable, Category = Create)
	static UWidgetClassStack* NewInitializedObject(APlayerController* InPC, UObject* InOwner);

	UFUNCTION(BlueprintCallable, Category = Create)
	static UWidgetClassStack* CreateInitializedDefaultSubobject(APlayerController* InPC, UObject* InOwner, const FName& InName);
	// ~ Creation End

	/**
	* Top widget (or nullptr if inactive, or no widget)
	*/
	UFUNCTION(BlueprintPure)
	UUserWidget* TopWidget() const;

	/**
	* Top creator widget.
	*/
	const FWidgetClassStackElement& TopCreatorElement() const;

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
	* Clears the stack.
	*/
	UFUNCTION(BlueprintCallable, Category = Stack)
	void Clear();

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
	void Push(const FWidgetClassStackElement& InElem);

	/**
	* Pops widget from top.
	* @returns: nullptr if stack is empty, otherwise widget.
	*/
	UFUNCTION(BlueprintCallable)
	void Pop();

	// ~UObject Begin
	virtual void BeginDestroy() override;
	// ~UObject End

protected:
	// ~Environment Begin
	UFUNCTION(BlueprintPure)
	APlayerController* GetPC() const;

	UPROPERTY()
	APlayerController* PC = nullptr;
	// ~Environment End

private:
	// ~Widget helpers Begin
	void HideAndDestroy_AllWidgets();

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
	/**
	* @returns: nullptr if stack is empty, otherwise widget.
	*/
	const FWidgetClassStack_ImplElem* TopElem() const;

	/**
	* @returns: nullptr if stack is empty, otherwise widget.
	*/
	FWidgetClassStack_ImplElem* TopElem();

	UPROPERTY()
	TArray<FWidgetClassStack_ImplElem> St;
	// ~Stack End
};

