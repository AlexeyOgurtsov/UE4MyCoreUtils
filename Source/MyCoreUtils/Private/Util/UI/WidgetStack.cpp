#include "WidgetStack.h"
#include "Kismet/GameplayStatics.h"
#include "UIUtilLib.h"
#include "../Core/LogUtilLib.h"

UWidgetStack::UWidgetStack()
{
	LogPrefix = FString::Printf(TEXT("WidgetStack \"%s\":"), *GetName());
}

void UWidgetStack::BeginDestroy()
{
	UE_LOG(MyLog, Log, TEXT("UWidgetStack::BeginDestroy..."));
	HideAllWidgets();
	St.Empty();
	UE_LOG(MyLog, Log, TEXT("UWidgetStack::BeginDestroy: Calling Super..."));
	Super::BeginDestroy();	
}

void UWidgetStack::HideAllWidgets()
{	
	UE_LOG(MyLog, Log, TEXT("%s Hiding all widgets"), *LogPrefix);
	for(UUserWidget* W : St)
	{
		UUIUtilLib::HideWidget(W);
	}
	UE_LOG(MyLog, Log, TEXT("%s Hiding all widgets DONE"), *LogPrefix);
}

bool UWidgetStack::IsEmpty() const
{
	return Num() == 0;
}

void UWidgetStack::Activate()
{
	UE_LOG(MyLog, Log, TEXT("%s Activating widget stack"), *LogPrefix);
	if(bActive)
	{
		UE_LOG(MyLog, Log, TEXT("%s Already active, skipping activation"), *LogPrefix);
		return;
	}
	bActive = true;

	AddTopWidgetToViewport();
}

void UWidgetStack::Deactivate()
{
	UE_LOG(MyLog, Log, TEXT("%s Deactivating widget stack"), *LogPrefix);
	if( ! bActive )
	{
		UE_LOG(MyLog, Log, TEXT("%s Already deactivated, skipping deactivation"), *LogPrefix);
		return;
	}
	bActive = false;

	HideAllWidgets();
}

void UWidgetStack::Empty()
{
	UE_LOG(MyLog, Log, TEXT("%s Clearing widget stack"), *LogPrefix);
	RemoveTopWidgetFromViewport_IfActive();
	St.Empty();
}

UUserWidget* UWidgetStack::Top() const
{
	if( ! IsEmpty() )
	{
		return St.Top();
	}
	else
	{
		return nullptr;
	}
}

void UWidgetStack::Push(UUserWidget* InWidget)
{
	UE_LOG(MyLog, Log, TEXT("%s Pushing widget"), *LogPrefix);

	check(InWidget);

	UE_LOG(MyLog, Log, TEXT("%s Widget is \"%s\" of class \"%s\""), *LogPrefix, *InWidget->GetName(), *InWidget->GetClass()->GetName());

	if( ! IsEmpty() )
	{
		RemoveTopWidgetFromViewport_IfActive();
	}
	St.Push(InWidget);
	AddTopWidgetToViewport_IfActive();
}

UUserWidget* UWidgetStack::Pop()
{
	UE_LOG(MyLog, Log, TEXT("UWidgetStack::Pop"));
	if(IsEmpty())
	{
		UE_LOG(MyLog, Log, TEXT("Skipping pop: stack is empty"));
		return nullptr;
	}
	else
	{
		return DoPop();
	}
}

UUserWidget* UWidgetStack::DoPop()
{
	UE_LOG(MyLog, Log, TEXT("UWidgetStack::DoPop..."));
	UE_LOG(MyLog, Log, TEXT("Stack size: %d"), Num());
	checkf( ! IsEmpty(), TEXT("Popping widget from the widget stack..."));
	checkf( Top(), TEXT("Top widget must be non-null"));
	UE_LOG(MyLog, Log, TEXT("Top widget is of class \"%s\" and named as \"%s\""), *Top()->GetClass()->GetName(), *Top()->GetName());
	// WARNING!!! We should NEVER check here that stack contains more than one element!
	UE_LOG(MyLog, Log, TEXT("%s Poppping widget"), *LogPrefix);
	RemoveTopWidgetFromViewport_IfActive();
	UUserWidget* W = St.Pop();	
	if( ! IsEmpty() )
	{
		AddTopWidgetToViewport_IfActive();
	}
	UE_LOG(MyLog, Log, TEXT("UWidgetStack::DoPop DONE"));
	return W;
}

void UWidgetStack::AddTopWidgetToViewport()
{
	if(UUserWidget* W = Top())
	{
		UE_LOG(MyLog, Log, TEXT("%s Adding top widget to viewport"), *LogPrefix);
		UUIUtilLib::ShowWidget(W);
	}
}

void UWidgetStack::RemoveTopWidgetFromViewport()
{
	if(UUserWidget* W = Top())
	{
		UE_LOG(MyLog, Log, TEXT("%s Removing top widget from viewport"), *LogPrefix);
		UUIUtilLib::HideWidget(W);
	}
}

void UWidgetStack::AddTopWidgetToViewport_IfActive()
{
	if(IsActive())
	{
		AddTopWidgetToViewport();
	}
}

void UWidgetStack::RemoveTopWidgetFromViewport_IfActive()
{
	if(IsActive())
	{
		RemoveTopWidgetFromViewport();
	}
}