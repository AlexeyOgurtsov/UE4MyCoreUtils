#include "ActorSelectionLib.h"
#include "Util\Core\LogUtilLib.h"

#include "GameFramework\Actor.h"
#include "Engine\World.h"
#include "Algo\Transform.h"

TSet<AActor*> UActorSelectionLib::SelectAtActor
(
	AActor* CenterObject,
	const FActorSelectionProps& SelectionProps
)	
{
	checkf(CenterObject, TEXT("CenterObject never should be nullptr when calling \"%s\""), TEXT(__FUNCTION__));
	return SelectAtPoint(CenterObject->GetActorLocation(), SelectionProps, CenterObject, TSet<AActor*>{CenterObject});
}

TSet<AActor*> UActorSelectionLib::SelectAtPoint
(
	const FVector& Point, 
	const FActorSelectionProps& SelectionProps,
	UObject* WorldContextObject,
	const TSet<AActor*>& IgnoreActors 
)	
{
	TSet<AActor*> Actors;
	if ( OverlapMultiByChannel(Actors, Point, SelectionProps.Query, WorldContextObject) )
	{
		Actors = Actors.Difference(IgnoreActors);
		FilterOutBySelectionRules(Actors, SelectionProps.Rule);
	}
	
	return Actors;
}

bool UActorSelectionLib::OverlapMultiByChannel(TSet<AActor*>& OutOverlappedActors, const FVector& Point, const FActorSelectionQuery& Query, UObject* WorldContextObject)
{
	TArray<FOverlapResult> Overlaps;
	const bool bAtLeastOneOverlapped = WorldContextObject->GetWorld()->OverlapMultiByChannel(Overlaps, Point, FQuat::Identity, Query.Channel, Query.GetShape(), Query.GetQueryParams(), Query.GetResponseParams());
	if (bAtLeastOneOverlapped)
	{
		OverlapResultArrayToActorSet(Overlaps, OutOverlappedActors);
		return true;
	}	
	return false;	
}

void UActorSelectionLib::OverlapResultArrayToActorSet(const TArray<FOverlapResult>& Overlaps, TSet<AActor*>& OutOverlappedActors)
{
	Algo::TransformIf
	(
		Overlaps, OutOverlappedActors, 
		[](const FOverlapResult& Overlap) { return Overlap.GetActor() != nullptr; },
		[](const FOverlapResult& Overlap) { return Overlap.GetActor(); }		
	);	
}

void UActorSelectionLib::FilterOutBySelectionRules(TSet<AActor*>& OutActors, const FActorSelectionRules& Rules)
{
	for (TSet<AActor*>::TIterator Itr = OutActors.CreateIterator(); Itr; ++Itr)
	{
		if ( ! ShouldActorBeSelected(*Itr, Rules) )
		{		
			Itr.RemoveCurrent();
		}
	}
}

bool UActorSelectionLib::ShouldActorBeSelected(const AActor* Actor, const FActorSelectionRules& SelectionRules)
{
	if (Actor == nullptr)
	{
		return false;
	}
	for (const FActorSelectionRule& Rule : SelectionRules.Rules)
	{
		// @TODO: filter by interface support
		if ( Rule.AllowedClasses.Num() > 0 && ! Rule.AllowedClasses.Contains(Actor->GetClass()) )
		{
			return false;
		}

		if ( Rule.AllowedTags.Num() > 0 && ( Rule.AllowedTags.Intersect(TSet<FName>(Actor->Tags)).Num() == 0 ) )
		{
			return false;
		}
	}
	// @TODO: Custom filter function support
	return true; 
}

FCollisionShape FActorSelectionQuery::GetShape() const
{
	FCollisionShape Shape;
	Shape.ShapeType = ECollisionShape::Type::Capsule;
	Shape.Capsule.Radius = CapsuleRadius;
	Shape.Capsule.HalfHeight = CapsuleHalfHeight;
	return Shape;
}

FActorSelectionQuery::FActorSelectionQuery()
:	QueryParams { FName(TEXT("ActorSelectionQueryTag")), /*bTraceComplex*/false, /*IgnoreActor*/nullptr }
,	ResponseParams{}
{
	// @TODO:
}

