#pragma once

#include "UObject/Interface.h"
#include "IActorSelector.generated.h"

UINTERFACE(BlueprintType, Meta=(CannotImplementInterfaceInBlueprint))
class UActorSelector : public UInterface
{
	GENERATED_BODY()
};

class IActorSelector
{
	GENERATED_BODY()

public:
	// ~Main interface Begin 
	// Requires implementation!
	UFUNCTION(BlueprintCallable, Category = Selection)
	virtual const TArray<AActor*>& GetActors() const = 0;

	UFUNCTION(BlueprintCallable, Category = Selection)
	virtual int32 GetSelectedIndex() const = 0;

	UFUNCTION(BlueprintCallable, Category = Selection)
	virtual void UpdateActorList() = 0;

	UFUNCTION(BlueprintCallable, Category = Selection)	
	virtual void SetSelectionIndex(int32 NewIndex) = 0;
	// ~Main interface End

	// ~Helper Begin
	bool IsActorSelected() const;

	void ResetSelection()
	{
		SetSelectionIndex(-1);
	}

	AActor* GetSelectedActor() const;
	AActor* GetSelectedActorChecked() const;

	APawn* GetSelectedPawn() const;
	APawn* GetSelectedPawnChecked() const;

	template<class T>
	T* GetSelectedActor() const
	{
		return Cast<T>(GetSelectedActor());
	}

	template<class T>
	T* GetSelectedActorChecked() const
	{
		return Cast<T>(GetSelectedActorChecked());
	}

	FString GetSelectedActorName() const;
	UClass* GetSelectedActorClass() const;
	FString GetSelectedActorClassName() const;

	int32 GetFirstIndex() const;
	int32 GetLastIndex() const;
	int32 GetNextIndexToSelect() const;
	int32 GetPreviousIndexToSelect() const;

	void SelectNext();
	void SelectPrevious();
	AActor* SelectFirstByClass(UClass* Class);
	AActor* SelectFirstByName(FName ObjectName);
	AActor* SelectFirst(AActor* const Actor);
	// ~Helper End
};