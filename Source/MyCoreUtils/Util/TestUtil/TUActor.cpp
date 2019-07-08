#include "TUActor.h"
#include "TUTypesLib.h"
#include "Util/Core/LogUtilLib.h"

ATUActor::ATUActor()
{
	M_LOGFUNC();
	LogThis();
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

void ATUActor::EndPlay(EEndPlayReason::Type InReason)
{
	M_LOGFUNC_IF(HasAnyTUFlags(ETUFlags::ExtLog));
	LogThisIf(HasAnyTUFlags(ETUFlags::ExtLog));
	Super::EndPlay(InReason);
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

void ATUActor::SetTUFlags(ETUFlags InTUFlags)
{
	LogTUFlags();
	TUFlags = InTUFlags;
}

bool ATUActor::HasAnyTUFlags(ETUFlags InFlagMask) const
{
	return ((TUFlags & InFlagMask) != ETUFlags::None);
}

bool ATUActor::HasAllTUFlags(ETUFlags InFlagMask) const
{
	return ((TUFlags & InFlagMask) == InFlagMask);
}

void ATUActor::LogTUFlags()
{
	LogThis();
	UTUTypesLib::LogTUFlags(GetTUFlags());
}
void ATUActor::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}

void ATUActor::LogThisIf(bool bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}
