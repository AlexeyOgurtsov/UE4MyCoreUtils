#pragma once

#include "ShowMouseStack.generated.h"

class APlayerController;

UCLASS()
class UShowMouseStack : public UObject
{
	GENERATED_BODY()

public:
	UShowMouseStack();

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UShowMouseStack* CreateInitializedDefaultSubobject(const FName& InName, APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = Creation)
	static UShowMouseStack* NewInitializedObject(const FName& InName, APlayerController* PC);	

	UFUNCTION(BlueprintPure, Category = Activity)
	bool IsActive() const { return bActive; }

	UFUNCTION(BlueprintCallable, Category = Activity)
	void Activate();

	UFUNCTION(BlueprintCallable, Category = Activity)
	void Deactivate();

	/**
	* Count of elements.
	*/
	UFUNCTION(BlueprintCallable)
	int32 Num() const { return St.Num(); }

	UFUNCTION(BlueprintPure)
	bool IsEmpty() const { return 0 == Num(); }

	/**
	* Push new state.
	*/
	UFUNCTION(BlueprintCallable)
	void Push(bool bInState);

	/**
	* Pop state.
	* Warning! Must be non-empty.
	*/
	UFUNCTION(BlueprintCallable)
	bool Pop();

	UFUNCTION(BlueprintPure)
	bool Top() const;

private:
	void SetTopState();
	void SetTopState_IfActive();

	// ~Logging Begin
	FString PrefixString;
	// ~Logging End

	UPROPERTY()
	APlayerController* PC = nullptr;
	
	UPROPERTY()
	bool bActive = false;

	UPROPERTY()
	TArray<bool> St;
};