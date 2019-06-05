#pragma once

/**
* Input mode stack.
*/

#include "InputModeLib.h"
#include "InputModeStack.generated.h"

UCLASS()
class UInputModeStack : public UObject
{
	GENERATED_BODY()

public:
	UInputModeStack();
	
	UFUNCTION(BlueprintCallable, Category = Creation)
	static UInputModeStack* CreateInitializedDefaultSubobject(const FName& InName, APlayerController* InPC);

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UInputModeStack* NewInitializedObject(const FName& InName, APlayerController* InPC);

	/**
	* When disabled, even stack is not updated.
	* By default enabled.
	*/
	UFUNCTION(BlueprintPure, Category = Enable)
	bool IsEnabled() const { return bEnabled; }

	UFUNCTION(BlueprintCallable, Category = Enable)
	void SetEnableState(bool bInEnabled);

	UFUNCTION(BlueprintPure, Category = Activity)
	bool IsActive() const { return bActive; }

	UFUNCTION(BlueprintCallable, Category = Activity)
	void Activate();

	UFUNCTION(BlueprintCallable, Category = Activity)
	void Deactivate();

	/**
	* @returns: Count of elements.
	*/
	int32 Num() const { return St.Num(); }
	
	/**
	* @returns: true if contains no elements.
	*/
	bool IsEmpty() const { return 0 == Num(); }

	/**
	* Pushs new input mode.
	*/
	void Push(const FInputModeStackElement& InElement);

	/**
	* Pops the input mode.
	* Warning! Count of elements must be greater than zero;
	*/
	FInputModeStackElement Pop();

	/**
	* Returns to input mode.
	* Warning! Count of elements must be greater than zero;
	*/
	const FInputModeStackElement& Top() const;

	// ~UObject Begin
	virtual void BeginDestroy() override;
	// ~UObject End
	
private:
	// ~Set Input Mode Begin
	void SetTopInputMode();
	void SetTopInputMode_IfActive();
	// ~Set Input Mode End

	// ~Logging helpers Begin
	FString PrefixString;
	// ~Logging helpers End

	UPROPERTY()
	bool bEnabled = true;

	UPROPERTY()
	bool bActive = false;

	UPROPERTY()
	APlayerController* PC = nullptr;

	UPROPERTY()
	TArray<FInputModeStackElement> St;
};