#include "IActorSelector.h"

#include "GameFramework\Pawn.h"

bool IActorSelector::IsActorSelected() const
{
	check(GetSelectedIndex() < GetActors().Num());
	return GetSelectedIndex() >= 0;
}

AActor* IActorSelector::GetSelectedActor() const
{
	return IsActorSelected() ? (GetActors()[GetSelectedIndex()]) : nullptr;
}

AActor* IActorSelector::GetSelectedActorChecked() const
{
	AActor* Selected = GetSelectedActor();
	checkf(Selected, TEXT("Actor must be selected when calling %s"), TEXT(__FUNCTION__));
	return Selected;
}

APawn* IActorSelector::GetSelectedPawn() const
{
	return GetSelectedActor<APawn>();
}

APawn* IActorSelector::GetSelectedPawnChecked() const
{
	return GetSelectedActorChecked<APawn>();
}

FString IActorSelector::GetSelectedActorName() const
{
	return IsActorSelected() ? *GetSelectedActor()->GetName() : FString(TEXT("nullptr"));
}

UClass* IActorSelector::GetSelectedActorClass() const
{
	return IsActorSelected() ? GetSelectedActor()->GetClass() : nullptr;
}

FString IActorSelector::GetSelectedActorClassName() const
{
	return IsActorSelected() ? GetSelectedActor()->GetClass()->GetName() : FString(TEXT("nullptr"));
}

int32 IActorSelector::GetFirstIndex() const
{
	if (GetActors().Num() > 0)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

int32 IActorSelector::GetLastIndex() const
{
	if (GetActors().Num() > 0)
	{
		return GetActors().Num() - 1;
	}
	else
	{
		return -1;
	}
}

int32 IActorSelector::GetNextIndexToSelect() const
{
	checkf( GetSelectedIndex() < GetActors().Num(), TEXT("Selected index must be in range when calling \"%s\""), TEXT(__FUNCTION__) );
	if ( !IsActorSelected() )
	{		
		return GetFirstIndex();
	}
	else if (GetSelectedIndex() == GetActors().Num() - 1)
	{
		// the last item is selected here => Keep the same index 
		return GetSelectedIndex();
	}
	else
	{
		return GetSelectedIndex() + 1;
	}
}

int32 IActorSelector::GetPreviousIndexToSelect() const
{
	checkf(GetSelectedIndex() < GetActors().Num(), TEXT("Selected index must be in range when calling \"%s\""), TEXT(__FUNCTION__));
	if ( !IsActorSelected() )
	{
		// the first item is selected here => Keep the same index 
		return GetFirstIndex();
	}
	if (GetSelectedIndex() == 0)
	{
		return GetSelectedIndex();
	}
	else
	{
		return GetSelectedIndex() - 1;
	}	
}

void IActorSelector::SelectNext()
{
	SetSelectionIndex(GetNextIndexToSelect());
}

void IActorSelector::SelectPrevious()
{	
	SetSelectionIndex(GetPreviousIndexToSelect());
}



AActor* IActorSelector::SelectFirstByClass(UClass* const Class)
{
	const int32 FoundIndex = GetActors().IndexOfByPredicate([Class](AActor* const A) { return A->GetClass() == Class; });
	if (FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
};

AActor* IActorSelector::SelectFirst(AActor* const Actor)
{
	const int32 FoundIndex = GetActors().Find(Actor);
	if (FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
}

AActor* IActorSelector::SelectFirstByName(FName const ObjectName)
{
	const int32 FoundIndex = GetActors().IndexOfByPredicate([ObjectName](AActor* const A) { return A->GetFName() == ObjectName; });
	if (FoundIndex < 0)
	{
		return nullptr;
	}
	SetSelectionIndex(FoundIndex);
	return GetSelectedActor();
}
