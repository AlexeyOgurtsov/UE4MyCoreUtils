#include "ActorSelectionComponent.h"
#include "Util\Selection\ActorSelectionLib.h"
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
	M_LOG(TEXT("%s: %s"), *LogPrefix, TEXT(__FUNCTION__));

	AActor* const PreviousSelectedActor = GetSelectedActor();

	Actors.Empty();

	FillActorList();
	Actors.Remove(nullptr);

	FixIndex(PreviousSelectedActor);

	LogState();
}

void UActorSelectionComponent::FillActorList()
{
	const TSet<AActor*> NewActors = UActorSelectionLib::SelectAtActor(GetAvatar(), SelectionProps);
	Actors.Append(NewActors.Array());
	Actors.Append(ManualActors);
}

void UActorSelectionComponent::AddWorldActorsByClass(UClass* const FilterClass)
{
	TArray<AActor*> ActorsOfClass;
	UGameplayStatics::GetAllActorsOfClass(this, FilterClass, ActorsOfClass);
	Actors.Append(ActorsOfClass);
}

void UActorSelectionComponent::SetSelectionIndex(int32 const NewIndex)
{
	M_LOG_IF(bShouldLog, TEXT("%s: Setting up selection index: NewIndex=%d (OldIndex=%d)"), *LogPrefix, NewIndex, GetSelectedIndex());
	SelectedIndex = NewIndex;
	ClampIndexIfShould();
	LogState();
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

void UActorSelectionComponent::LogState() const
{	
	M_LOG(TEXT("%s: Actor \"%s\" of class \"%s\" (index=%d) selected ( NumActorsToSelect=%d )"), *LogPrefix, *GetSelectedActorName(), *GetSelectedActorClassName(), GetSelectedIndex(), GetActors().Num());
}

AActor* UActorSelectionComponent::GetAvatar() const
{
	AController* const OwnerController = Cast<AController>(GetOwner());
	if (OwnerController)
	{
		APawn* const OwnerPawn = OwnerController->GetPawn();
		if (OwnerPawn)
		{
			return OwnerPawn;
		}
	}
	
	return GetOwner();
}