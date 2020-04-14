#include "TemplPlayerController.h"
#include "TemplPawn.h"
#include "TemplConfig.h"

#include "Util/Core/LogUtilLib.h"

MyPCType::ATemplPlayerController()
{
}
 
void MyPCType::BeginPlay()
{
	M_LOGFUNC();

	Super::BeginPlay();
}

void MyPCType::Axis_LookPitch(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_LookPitch(P, InAmount);
}

void MyPCType::Axis_LookYaw(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_LookYaw(P, InAmount);
}

void MyPCType::Axis_Forward(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Forward(P, InAmount);
}

void MyPCType::Axis_Right(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Right(P, InAmount);
}

void MyPCType::Axis_Up(APawn* P, float InAmount)
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Axis_Up(P, InAmount);
}

void MyPCType::Action_Use()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_Use();
}

void MyPCType::Action_UseTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_UseTwo();
}

void MyPCType::Action_UseThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_UseThree();
}

void MyPCType::Action_Fire()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_Fire();
}

void MyPCType::Action_FireTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_FireTwo();
}

void MyPCType::Action_FireThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_FireThree();
}

void MyPCType::Action_SelectZero()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectZero();
}

void MyPCType::Action_SelectOne()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectOne();
}

void MyPCType::Action_SelectTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectTwo();
}

void MyPCType::Action_SelectThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectThree();
}

void MyPCType::Action_SelectFour()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectFour();
}

void MyPCType::Action_SelectFive()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectFive();
}

void MyPCType::Action_SelectSix()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectSix();
}

void MyPCType::Action_SelectSeven()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectSeven();
}

void MyPCType::Action_SelectEight()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectEight();
}

void MyPCType::Action_SelectNine()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_SelectNine();
}

void MyPCType::Action_OpenGameMenu()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_OpenGameMenu();
}

void MyPCType::Action_CloseGameMenu()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_CloseGameMenu();
}

void MyPCType::Action_DebugOne()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_DebugOne();
}

void MyPCType::Action_DebugTwo()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_DebugTwo();
}

void MyPCType::Action_DebugThree()
{
	// ACTION OVERRIDE POINT:
	// If you want to override, REPLACE(!) the given super call
	Super::Action_DebugThree();
}

MyPawnType* MyPCType::GetMyPawn() const
{
	return Cast<MyPawnType>(GetPawn());
}

MyPawnType* MyPCType::GetMyPawnLogged(ELogFlags InLogFlags) const
{
	MyPawnType* const P = GetMyPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetMyPawn() returned NULL"));
	}
	return P;
}

MyPawnType* MyPCType::GetMyPawnChecked() const
{
	MyPawnType* const P = GetMyPawn();
	checkf(P, TEXT("GetMyPawn must return non-NULL pawn!"));
	return P;
}

