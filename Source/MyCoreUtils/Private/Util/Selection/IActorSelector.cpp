#include "IActorSelector.h"

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

void IActorSelector::SelectNext()
{
	if (!IsActorSelected())
	{
		return;
	}
	if (GetSelectedIndex() >= GetActors().Num() - 1)
	{
		return;
	}
	SetSelectionIndex(GetSelectedIndex() + 1);
}

void IActorSelector::SelectPrevious()
{
	if (!IsActorSelected())
	{
		return;
	}
	if (GetSelectedIndex() < 1)
	{
		return;
	}
	SetSelectionIndex(GetSelectedIndex() - 1);
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