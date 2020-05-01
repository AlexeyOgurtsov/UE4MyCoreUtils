#include "TUActor.h"
#include "TUTypesLib.h"
#include "Util/Core/LogUtilLib.h"

#include "DrawDebugHelpers.h"

ATUActor::ATUActor()
{
	M_LOGFUNC();
	LogThis();
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ATUActor::PostLoad()
{	
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PostLoad();
}

void ATUActor::BeginPlay()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::BeginPlay();
}

void ATUActor::EndPlay(EEndPlayReason::Type const InReason)
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::EndPlay(InReason);
}

void ATUActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	RenderBoundsIfShould();
}

void ATUActor::PreRegisterAllComponents()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PreRegisterAllComponents();
}

void ATUActor::PostRegisterAllComponents()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PostRegisterAllComponents();
}

void ATUActor::PostActorCreated()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PostActorCreated();
}

void ATUActor::PreInitializeComponents()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PreInitializeComponents();
}

void ATUActor::PostInitializeComponents()
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::PostInitializeComponents();
}

void ATUActor::OnConstruction(const FTransform& Transform)
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::OnConstruction(Transform);
}

void ATUActor::SetTUFlags(ETUFlags const InTUFlags)
{
	TUConfig.SetFlags(InTUFlags);
}
void ATUActor::UnsetTUFlags(ETUFlags const InFlagMask)
{
	TUConfig.UnsetFlags(InFlagMask);
}
bool ATUActor::HasAnyTUFlags(ETUFlags const InFlagMask) const
{
	return TUConfig.HasAnyFlags(InFlagMask);
}

bool ATUActor::HasAllTUFlags(ETUFlags const InFlagMask) const
{
	return TUConfig.HasAllFlags(InFlagMask);
}

void ATUActor::LogTUFlags()
{
	LogThis();
	UTUTypesLib::LogTUFlags(TUConfig.GetFlags());
}
void ATUActor::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}

void ATUActor::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUActor::RenderBoundsIfShould()
{
	if (TUConfig.RenderDebugBounds.bShouldRender)
	{
		FVector BoundsBoxCenter;
		FVector BoundsBoxExtent;
		GetActorBounds(TUConfig.RenderDebugBounds.bConsiderOnlyCollidingComponents, BoundsBoxCenter, BoundsBoxExtent);
		const bool bPersistentLines = false;
		const float BoxLifetime = 1.0F;
		DrawDebugBox(GetWorld(), BoundsBoxCenter, BoundsBoxExtent, TUConfig.RenderDebugBounds.Color, bPersistentLines, BoxLifetime, TUConfig.RenderDebugBounds.DepthPriority, TUConfig.RenderDebugBounds.Thickness);
	}
}
