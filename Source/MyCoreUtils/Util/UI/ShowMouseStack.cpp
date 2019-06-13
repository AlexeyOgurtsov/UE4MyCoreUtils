#include "ShowMouseStack.h"
#include "GameFramework/PlayerController.h"
#include "../Core/LogUtilLib.h"

UShowMouseStack::UShowMouseStack()
{
	PrefixString = FString::Printf(TEXT("Show mouse stack: \"%s\""), *GetName());
}

UShowMouseStack* UShowMouseStack::CreateInitializedDefaultSubobject(const FName& InName, APlayerController* PC)
{
	check(PC);

	UShowMouseStack* St = PC->CreateDefaultSubobject<UShowMouseStack>(InName);
	St->PC = PC;

	return St;
}

UShowMouseStack* UShowMouseStack::NewInitializedObject(const FName& InName, APlayerController* PC)
{
	check(PC);

	UShowMouseStack* St = NewObject<UShowMouseStack>(PC, UShowMouseStack::StaticClass(), InName);
	St->PC = PC;

	return St;
}

void UShowMouseStack::Activate()
{
	UE_LOG(MyLog, Log, TEXT("%s Activating"), *PrefixString);
	if( IsActive() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Already active - skipping activation"), *PrefixString);
		return;
	}
	bActive = true;
	if( ! IsEmpty() )
	{
		SetTopState();
	}
}

void UShowMouseStack::Deactivate()
{
	UE_LOG(MyLog, Log, TEXT("%s Deactivating"), *PrefixString);
	if( ! IsActive() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Already inactive - skipping deactivation"), *PrefixString);
		return;
	}
	bActive = false;
}

void UShowMouseStack::Push(bool bInState)
{
	St.Push(bInState);
	SetTopState_IfActive();
}

bool UShowMouseStack::Pop()
{
	checkf(Num() > 1, TEXT("%s Pop() maybe called only if stack contains more than one element"), *PrefixString);
	bool bNewState = St.Pop();
	SetTopState_IfActive();
	return bNewState;
}

bool UShowMouseStack::Top() const
{
	checkf( ! IsEmpty(), TEXT("%s Top() maybe called only if stack is non-empty"), *PrefixString);
	return St.Top();
}

void UShowMouseStack::SetTopState()
{
	bool const bNewValue = Top();
	UE_LOG(MyLog, Log, TEXT("%s Setting up bShowMouseCursorState=\"%s\""), *PrefixString, (bNewValue ? TEXT("YES") : TEXT("no")));
	PC->bShowMouseCursor = bNewValue;
}

void UShowMouseStack::SetTopState_IfActive()
{
	if( IsActive() )
	{
		SetTopState();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s SetTopState skipping: inactive"), *PrefixString);
	}
}