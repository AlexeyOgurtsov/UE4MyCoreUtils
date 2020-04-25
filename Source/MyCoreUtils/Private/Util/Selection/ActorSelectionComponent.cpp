#include "ActorSelectionComponent.h"
#include "Util\Core\LogUtilLib.h"
#include "GameFramework\Actor.h"
#include "Kismet\GameplayStatics.h"

/**
* TODO Debug:
* 1. Consider change TArray to TSet
* 2. Consider to use weak references to actors
* 
* TODO Helpers:
* Spawn invisible actor and add (+useful for inventory).
*
* TODO Filtering
* 1. By interface
* 2. By tags
* 3. By distance
* 4. Custom filtering functions
*
* TODO Logging
* TODO Events
*/

UActorSelectionComponent::UActorSelectionComponent()
{
	bEditableWhenInherited = true;
}


void UActorSelectionComponent::PostInitProperties() 
{
	Super::PostInitProperties();
	LogPrefix = FString::Printf(TEXT("SELCOMP \"%s\" (cl=%s)"), *GetName(), *GetClass()->GetName());
	PrimaryComponentTick.bCanEverTick = bUpdateActorListOnTick;
}

void UActorSelectionComponent::BeginPlay()
{
	Super::BeginPlay();
	if(bUpdateActorListOnBeginPlay)
	{
		UpdateActorList();
	}
}

void UActorSelectionComponent::TickComponent(float DeltaSeconds, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if(bUpdateActorListOnTick)
	{
		UpdateActorList();
	}
}

bool UActorSelectionComponent::IsSelected() const
{
	check(SelectedIndex < Actors.Num());
	return SelectedIndex >= 0;
}

void UActorSelectionComponent::UpdateActorList()
{
	AActor* const PreviousSelectedActor = GetSelectedActor();

	Actors.Empty();

	const TArray<UClass*> RealFilterClasses = (FilterClasses.Num() == 0) ? TArray<UClass*>{AActor::StaticClass()} : FilterClasses;
	for(int32 FilterClassIndex = 0; FilterClassIndex < RealFilterClasses.Num(); FilterClassIndex++)
	{
		UClass* FilterClass = RealFilterClasses[FilterClassIndex];
		AddWorldActorsByClass(FilterClass);
	}

	Actors.Append(ManualActors);

	Actors.Remove(nullptr);

	FixIndex(PreviousSelectedActor);
}
void UActorSelectionComponent::AddWorldActorsByClass(UClass* const FilterClass)
{
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, FilterClass, ActorsOfClass);
	Actors.Append(ActorsOfClass);
}
	
AActor* UActorSelectionComponent::GetSelectedActor() const
{
	return IsSelected() ? (Actors[SelectedIndex]) : nullptr;
}

AActor* UActorSelectionComponent::GetSelectedActorChecked() const
{
	AActor* Selected = GetSelectedActor();
	checkf(Selected, TEXT("Actor must be selected when calling %s"), TEXT(__FUNCTION__));
	return Selected;
}

APawn* UActorSelectionComponent::GetSelectedPawn() const
{
	return GetSelectedActor<APawn>();
}

APawn* UActorSelectionComponent::GetSelectedPawnChecked() const
{
	return GetSelectedActorChecked<APawn>();
}

AActor* UActorSelectionComponent::SelectFirstByClass(UClass* const Class)
{
	const int32 FoundIndex = Actors.IndexOfByPredicate([Class](AActor* const A){ return A->GetClass() == Class; });
	if(FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
};

AActor* UActorSelectionComponent::SelectFirst(AActor* const Actor)
{
	const int32 FoundIndex = Actors.Find(Actor);
	if(FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
}

AActor* UActorSelectionComponent::SelectFirstByName(FName const ObjectName)
{
	const int32 FoundIndex = Actors.IndexOfByPredicate([ObjectName](AActor* const A){ return A->GetFName() == ObjectName; });
	if(FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
}


void UActorSelectionComponent::SetSelectionIndex(int32 const NewIndex)
{
	SelectedIndex = NewIndex;
	ClampIndexIfShould();
}

void UActorSelectionComponent::FixIndex(AActor* const PreviousSelectedActor)
{
	if(PreviousSelectedActor)
	{
		const int32 NewIndex = Actors.Find(PreviousSelectedActor);
		SelectedIndex = NewIndex;
	}
}

void UActorSelectionComponent::ClampIndexIfShould()
{
	if(SelectedIndex < Actors.Num())
	{
		return;
	}
	SelectedIndex = (Actors.Num() - 1);
}

void UActorSelectionComponent::SelectNext()
{
	M_LOG(TEXT("%s: Selecting previous"), *LogPrefix);
	if( ! IsSelected() )
	{
		return;
	}
	if( SelectedIndex >= Actors.Num() - 1 )
	{
		return;
	}
	SetSelectionIndex(SelectedIndex + 1);
}

void UActorSelectionComponent::SelectPrevious()
{
	M_LOG(TEXT("%s: Selecting next"), *LogPrefix);
	if( ! IsSelected() )
	{
		return;
	}
	if( SelectedIndex < 1 )
	{
		return;
	}
	SetSelectionIndex(SelectedIndex - 1);
}
