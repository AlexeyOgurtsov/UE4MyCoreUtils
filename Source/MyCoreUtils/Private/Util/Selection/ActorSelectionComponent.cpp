#include "ActorSelectionComponent.h"
#include "Util\Core\LogUtilLib.h"
#include "GameFramework\Actor.h"
#include "Kismet\GameplayStatics.h"

/**
* TODO Scheme:
* 1. Create a special container type - array that makes events;
* 2. Refactor the component to use that special array;
*
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
	if (SelectedIndex < Actors.Num())
	{
		return;
	}
	SelectedIndex = (Actors.Num() - 1);
}
