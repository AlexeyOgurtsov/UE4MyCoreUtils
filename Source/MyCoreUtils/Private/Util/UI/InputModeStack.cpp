#include "InputModeStack.h"
#include "InputModeLib.h"

#include "../Core/LogUtilLib.h"

#include "GameFramework/PlayerController.h"

#define IMS_SKIP_IF_DISABLED_RET(OpName, ReturnOp)\
{\
	if( ! IsEnabled() )\
	{\
		UE_LOG(MyLog, Warning, TEXT("%s Skipping operation \"%s\" (DISABLED)"), *PrefixString, TEXT(OpName));\
		ReturnOp;\
	}\
}

#define IMS_SKIP_IF_DISABLED(OpName)\
{\
	if( ! IsEnabled() )\
	{\
		UE_LOG(MyLog, Warning, TEXT("%s Skipping operation \"%s\" (DISABLED)"), *PrefixString, TEXT(OpName));\
		return;\
	}\
}



UInputModeStack::UInputModeStack()
{
	PrefixString = FString::Printf(TEXT("Input mode stack \"%s\":"), *GetName());
}

void UInputModeStack::BeginDestroy()
{
	UE_LOG(MyLog, Log, TEXT("InputModeStack: BeginDestroy..."));
	Super::BeginDestroy();
IMS_SKIP_IF_DISABLED("BeginDestroy");
	St.Empty();
}

void UInputModeStack::SetEnableState(bool bInEnabled)
{
	bEnabled = bInEnabled;
	if( ! bInEnabled )
	{
		UE_LOG(MyLog, Warning, TEXT("%s Disabling InputModeStack"), *PrefixString);
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s Enabling InputModeStack"), *PrefixString);
	}
}

void UInputModeStack::Activate()
{	
	UE_LOG(MyLog, Log, TEXT("%s Activating..."), *PrefixString);
IMS_SKIP_IF_DISABLED("Activate");
	if( IsActive() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping activation - already active"), *PrefixString);
		return;
	}
	bActive = true;

	if( ! IsEmpty() )
	{
		SetTopInputMode();
	}
}

void UInputModeStack::Deactivate()
{
	UE_LOG(MyLog, Log, TEXT("%s Deactivating..."), *PrefixString);
IMS_SKIP_IF_DISABLED("Deactivate");
	if( ! IsActive() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping deactivation - already deactivated"), *PrefixString);
		return;
	}
	bActive = false;
}

UInputModeStack* UInputModeStack::CreateInitializedDefaultSubobject(const FName& InName, APlayerController* InPC)
{
	check(InPC);

	UInputModeStack* St = InPC->CreateDefaultSubobject<UInputModeStack>(InName);
	St->PC = InPC;

	return St;
}


UInputModeStack* UInputModeStack::NewInitializedObject(const FName& InName, APlayerController* InPC)
{
	check(InPC);

	UInputModeStack* St = NewObject<UInputModeStack>(InPC, UInputModeStack::StaticClass(), InName);
	St->PC = InPC;

	return St;
}

void UInputModeStack::Push(const FInputModeStackElement& InElement)
{
	UE_LOG(MyLog, Log, TEXT("%s Pushing..."), *PrefixString);
	UE_LOG(MyLog, Log, TEXT("%s Mode=%s"), *PrefixString, *UInputModeLib::InputModeToString(InElement));

IMS_SKIP_IF_DISABLED("Push");
	St.Push(InElement);

	SetTopInputMode_IfActive();
}

FInputModeStackElement UInputModeStack::Pop()
{
IMS_SKIP_IF_DISABLED_RET("Pop", {return FInputModeStackElement{};} );	

	checkf( Num() > 1, TEXT("%s When popping stack must contain more than one element"), *PrefixString);

	FInputModeStackElement Element = St.Pop();
	
	SetTopInputMode_IfActive();

	return Element;
}

void UInputModeStack::SetTopInputMode_IfActive()
{
	if( IsActive() )
	{
		SetTopInputMode();
	}
}

void UInputModeStack::SetTopInputMode()
{
	const FInputModeStackElement& InputMode = Top();
	UE_LOG(MyLog, Log, TEXT("%s Setting up top input mode"), *PrefixString);
	UE_LOG(MyLog, Log, TEXT("%s InputMode: %s"), *PrefixString, *UInputModeLib::InputModeToString(InputMode));
	UInputModeLib::SetInputMode(PC, InputMode);
}

const FInputModeStackElement& UInputModeStack::Top() const
{
	checkf( ! IsEmpty(), TEXT("%s When getting Top stack must be non-empty"), *PrefixString);

	return St.Top();
}