#pragma once

#include "Components/ActorComponent.h"
#include "ActorSelectionComponent.generated.h"

UCLASS(ClassGroup=(Selection), Meta=(BlueprintSpawnableComponent))
class UActorSelectionComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, category=Selection)
	TArray<UClass*> FilterClasses;

	UPROPERTY(EditAnywhere, category=Selection)
	uint32 bUpdateActorListOnBeginPlay = true;

	UPROPERTY(EditAnywhere, category=Selection)
	uint32 bUpdateActorListOnTick = false;

public:
	/**
	* This actors are always included in the main actors list.
	* May not obet to the actor collection rules.
	* WARN!!! Actors list must be updated to take effect!!!
	*/
	UPROPERTY(BlueprintReadWrite, Category = Selection)
	TArray<AActor*> ManualActors;

	UActorSelectionComponent();

	virtual void PostInitProperties() override;
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	const TArray<AActor*>& GetManualActors() const { return ManualActors; }
	void SetManualActors(const TArray<AActor*>& InManualActors) { ManualActors = InManualActors; }

	UFUNCTION(BlueprintCallable, Category=Selection)
	void ClearManualActors() { ManualActors.Empty(); }

	UFUNCTION(BlueprintCallable, Category=Selection)
	void AddManualActor(AActor* InActor) { ManualActors.Add(InActor); }

	UFUNCTION(BlueprintCallable, Category=Selection)
	void RemoveManualActor(AActor* InActor) { ManualActors.Remove(InActor); }

	const TArray<AActor*>& GetActors() const { return Actors; }
	int32 GetSelectedIndex() const { return SelectedIndex; }

	/**
	* @return Returns actor that is selected right now. 
	* Or returns nullptr if no actor is selected.
	*/
	UFUNCTION(BlueprintCallable, Category=Selection, Meta=(DisplayName="GetSelectedActor"))
	AActor* K2_GetSelectedActor() const
	{
		return GetSelectedActor();
	}

	/**
	* @return Returns actor that is selected right now. 
	* Checks (with checkf, that index is selected).
	*/
	UFUNCTION(BlueprintCallable, Category=Selection, Meta=(DisplayName="GetSelectedActor"))
	AActor* K2_GetSelectedActorChecked() const
	{
		return GetSelectedActorChecked();
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

	UFUNCTION(Category=Selection)
	bool IsSelected() const;

	UFUNCTION(BlueprintCallable, Category=Selection)
	void UpdateActorList();

	UFUNCTION(BlueprintCallable, Category=Selection)
	void SetSelectionIndex(int32 NewIndex);

	UFUNCTION(BlueprintCallable, Category=Selection)
	void ResetSelection()
	{
		SetSelectionIndex(-1);
	}

	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectNext();

	UFUNCTION(BlueprintCallable, Category=Selection)
	void SelectPrevious();

	UFUNCTION(BlueprintCallable, Category=Selection)
	AActor* SelectFirstByClass(UClass* Class);

	UFUNCTION(BlueprintCallable, Category=Selection)
	AActor* SelectFirstByName(FName ObjectName);

	UFUNCTION(BlueprintCallable, Category=Selection)
	AActor* SelectFirst(AActor* const Actor);

protected:
	void AddWorldActorsByClass(UClass* FilterClass);

	UPROPERTY(BlueprintReadOnly, Category = Selection)
	TArray<AActor*> Actors;

	UPROPERTY(BlueprintReadOnly, Category = Selection)
	int32 SelectedIndex = -1;

	FString LogPrefix;

	void FixIndex(AActor* PreviousSelectedActor);
	void ClampIndexIfShould();
};
