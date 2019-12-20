#include "TUAIController.h"
#include "TUPawn.h"
#include "Util/Core/LogUtilLib.h"

ATUAIController::ATUAIController()
{
	M_LOGFUNC();
	LogThis();
}

void ATUAIController::PostInitProperties()
{
	Super::PostInitProperties();

	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
}

void ATUAIController::PreRegisterAllComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PreRegisterAllComponents();
}

void ATUAIController::PostRegisterAllComponents() 
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PostRegisterAllComponents();
}

void ATUAIController::PreInitializeComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PreInitializeComponents();
}

void ATUAIController::PostInitializeComponents()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::PostInitializeComponents();
}

void ATUAIController::BeginPlay()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::BeginPlay();
}

void ATUAIController::EndPlay(EEndPlayReason::Type InReason)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::EndPlay(InReason);
}

void ATUAIController::OnPossess(APawn* InPawn)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (BEFORE Super)"), GetPawn());
	Super::OnPossess(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (AFTER Super)"), GetPawn());
}

void ATUAIController::OnUnPossess()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	Super::OnUnPossess();
}

void ATUAIController::SetPawn(APawn* InPawn)
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (BEFORE Super)"), GetPawn());
	Super::SetPawn(InPawn);
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("GetPawn() (AFTER Super)"), GetPawn());
}

void ATUAIController::PawnBeginPlayEnded_Implementation()
{
	M_LOGFUNC_IF(TUConfig.bLogBigEvents);
	LogThisIf(TUConfig.bLogBigEvents);
}

ATUPawn* ATUAIController::GetTUPawn() const
{
	return Cast<ATUPawn>(GetPawn());
}

ATUPawn* ATUAIController::GetMyTUPawnLogged(ELogFlags InLogFlags) const
{
	ATUPawn* const P = GetTUPawn();
	if(P == nullptr)
	{
		M_LOG_ERROR_IF_FLAGS(InLogFlags, TEXT("GetTUPawn() returned NULL"));
	}
	return P;
}

ATUPawn* ATUAIController::GetMyTUPawnChecked() const
{
	ATUPawn* const P = GetTUPawn();
	checkf(P, TEXT("GetTUPawn() must return non-NULL pawn!"));
	return P;
}

void ATUAIController::LogThisIf(bool const bInShouldLog)
{
	if(bInShouldLog)
	{
		LogThis();
	}
}

void ATUAIController::LogThis()
{
	ULogUtilLib::LogKeyedNameClassSafeC(TEXT("This"), this);
}
