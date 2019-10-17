#include "ProjectileDemoPlayerController.h"
#include "ProjectileDemoPawn.h"
#include "ProjectileDemoConfig.h"

#include "Util/Core/LogUtilLib.h"

MyProjectileDemoPCType::AProjectileDemoPlayerController()
{
}
 
void MyProjectileDemoPCType::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();
}


MyProjectileDemoPawnType* MyProjectileDemoPCType::GetMyPawn() const
{
	return Cast<MyProjectileDemoPawnType>(GetPawn());
}

MyProjectileDemoPawnType* MyProjectileDemoPCType::GetMyPawnLogged(ELogFlags InLogFlags) const
{
	MyProjectileDemoPawnType* const P = GetMyPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPawn() returned NULL"));
	}
	return P;
}

MyProjectileDemoPawnType* MyProjectileDemoPCType::GetMyPawnChecked() const
{
	MyProjectileDemoPawnType* const P = GetMyPawn();
	checkf(P, TEXT("GetMyPawn must return non-NULL pawn!"));
	return P;
}

void MyProjectileDemoPCType::Action_Fire()
{
	GetMyPawnChecked()->LaunchProjectile();	
}

void MyProjectileDemoPCType::Action_FireTwo()
{
	Super::Action_FireTwo();
}

void MyProjectileDemoPCType::Action_FireThree()
{
	Super::Action_FireThree();
}
