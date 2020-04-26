#pragma once

#include "Components/ActorComponent.h"
#include "Util/Selection/IActorSelector.h"
#include "Util/Selection/ActorSelectionTypes.h"
#include "ActorSelectionComponent.generated.h"

UCLASS(ClassGroup=(Selection), Meta=(BlueprintSpawnableComponent))
class UActorSelectionComponent
:	public UActorComponent
,	public IActorSelector
{
	GENERATED_BODY()
	
	// @TODO: Remove
	UPROPERTY(EditAnywhere, category=Selection)
	TSet<UClass*> FilterClasses;

	UPROPERTY(EditAnywhere, category=Selection)
	uint32 bUpdateActorListOnBeginPlay = true;

	UPROPERTY(EditAnywhere, category=Selection)
	uint32 bUpdateActorListOnTick = false;

	UPROPERTY(EditAnywhere, category = Selection)
	uint32 bShouldLog = true;

public:
	UPROPERTY(EditAnywhere, Category = Selection, Meta = (ShowOnlyInnerProperties = true))
	FActorSelectionProps SelectionProps;

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

	// ~IActorSelector Begin
	virtual const TArray<AActor*>& GetActors() const override { return Actors; }
	virtual int32 GetSelectedIndex() const override { return SelectedIndex; }	
	virtual void UpdateActorList() override;
	virtual void SetSelectionIndex(int32 NewIndex) override;	
	// ~IActorSelector End

	void LogState() const;

protected:
	void FillActorList();
	void AddWorldActorsByClass(UClass* FilterClass);

	UPROPERTY(BlueprintReadOnly, Category = Selection)
	TArray<AActor*> Actors;

	UPROPERTY(BlueprintReadOnly, Category = Selection)
	int32 SelectedIndex = -1;

	FString LogPrefix;

	void FixIndex(AActor* PreviousSelectedActor);
	void ClampIndexIfShould();

	AActor* GetAvatar() const;
};
