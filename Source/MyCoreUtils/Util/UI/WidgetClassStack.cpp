#include "WidgetClassStack.h"

#include "UIUtilLib.h"
#include "Util/Core/LogUtilLib.h"
#include "Kismet/GameplayStatics.h"

namespace
{
		void HideAndDestroyWidget_IfCreated(UWidgetClassStack* InSender, FWidgetClassStack_ImplElem* InStackElem);
		void CreateAndShowWidget(UWidgetClassStack* InSender, APlayerController* InPC, FWidgetClassStack_ImplElem* InStackElem, const FName& InName);
		void HideAndDestroyWidget(UWidgetClassStack* InSender, FWidgetClassStack_ImplElem* InStackElem);

		void HideAndDestroyWidget_IfCreated(UWidgetClassStack* InSender, FWidgetClassStack_ImplElem* InStackElem)
		{
			check(InSender);
			check(InStackElem);
			if(false == InStackElem->IsWidgetCreated())
			{
				UE_LOG(MyLog, Log, TEXT("Skipping hiding widget: widget is not created"));
				return;
			}
			HideAndDestroyWidget(InSender, InStackElem);
		}

		void CreateAndShowWidget(UWidgetClassStack* InSender, APlayerController* InPC, FWidgetClassStack_ImplElem* InStackElem, const FName& InName)
		{
			check(InSender);
			UE_LOG(MyLog, Log, TEXT("CreateAndShowWidget..."));

			check(InStackElem)
			check( ! InStackElem->IsWidgetCreated() );
	
			InStackElem->Widget = UWidgetClassStackLib::CreateWidget(InPC, InStackElem->CreatorElement);
			UUIUtilLib::ShowWidget(InStackElem->Widget);
	
			UE_LOG(MyLog, Log, TEXT("CreateAndShowWidget DONE"));
		}

		void HideAndDestroyWidget(UWidgetClassStack* InSender, FWidgetClassStack_ImplElem* InStackElem)
		{
			check(InSender);
			UE_LOG(MyLog, Log, TEXT("HideAndDestroyWidget..."));

			check(InStackElem);
			check(InStackElem->IsWidgetCreated());
	
			UUIUtilLib::HideWidget(InStackElem->Widget);	
			InStackElem->Widget = nullptr;

			UE_LOG(MyLog, Log, TEXT("HideAndDestroyWidget DONE"));
		}
} // anonymous namespace

FWidgetClassStack_ImplElem::FWidgetClassStack_ImplElem()
{
}

FWidgetClassStack_ImplElem::FWidgetClassStack_ImplElem(const FWidgetClassStackElement& InCreatorElement) :	
	CreatorElement(InCreatorElement)
{
}

bool FWidgetClassStack_ImplElem::IsWidgetCreated() const
{
	return Widget != nullptr;
}

UWidgetClassStack::UWidgetClassStack()
{
	LogPrefix = FString::Printf(TEXT("WidgetClassStack \"%s\":"), *GetName());
}

UWidgetClassStack* UWidgetClassStack::NewInitializedObject(APlayerController* InPC, UObject* InOwner)
{
	check(InPC);
	check(InOwner);

	UWidgetClassStack* S = NewObject<UWidgetClassStack>(InOwner, UWidgetClassStack::StaticClass());
	check(S);
	S->PC = InPC;
	return S;
}

UWidgetClassStack* UWidgetClassStack::CreateInitializedDefaultSubobject(APlayerController* InPC, UObject* InOwner, const FName& InName)
{
	check(InPC);
	check(InOwner);

	UWidgetClassStack* S = InOwner->CreateDefaultSubobject<UWidgetClassStack>(InName);
	check(S);
	S->PC = InPC;
	return S;
}

void UWidgetClassStack::BeginDestroy()
{
	UE_LOG(MyLog, Log, TEXT("%s BeginDestroy..."), *LogPrefix);
	Clear();
	UE_LOG(MyLog, Log, TEXT("%s BeginDestroy: Calling Super..."), *LogPrefix);
	Super::BeginDestroy();	
}

void UWidgetClassStack::Clear()
{
	UE_LOG(MyLog, Log, TEXT("%s Clear..."), *LogPrefix);
	HideAndDestroy_AllWidgets();
	St.Empty();
}

void UWidgetClassStack::HideAndDestroy_AllWidgets()
{
	UE_LOG(MyLog, Log, TEXT("%s Hiding and destroying all widgets:"), *LogPrefix);
	for(FWidgetClassStack_ImplElem& StackElem : St)
	{
		HideAndDestroyWidget_IfCreated(this, &StackElem);
	}
}

bool UWidgetClassStack::IsEmpty() const
{
	return Num() == 0;
}

void UWidgetClassStack::Activate()
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

void UWidgetClassStack::Deactivate()
{
	UE_LOG(MyLog, Log, TEXT("%s Deactivating widget stack"), *LogPrefix);
	if( ! bActive )
	{
		UE_LOG(MyLog, Log, TEXT("%s Already deactivated, skipping deactivation"), *LogPrefix);
		return;
	}
	bActive = false;

	HideAndDestroy_AllWidgets();
}

void UWidgetClassStack::Empty()
{
	UE_LOG(MyLog, Log, TEXT("%s Clearing widget stack"), *LogPrefix);
	RemoveTopWidgetFromViewport_IfActive();
	St.Empty();
}

void UWidgetClassStack::Push(const FWidgetClassStackElement& InElem)
{
	UE_LOG(MyLog, Log, TEXT("%s Push"), *LogPrefix);

	RemoveTopWidgetFromViewport_IfActive();	
	St.Push(InElem);
	AddTopWidgetToViewport_IfActive();
}

void UWidgetClassStack::Pop()
{
	UE_LOG(MyLog, Log, TEXT("%s Pop"), *LogPrefix);
	
	RemoveTopWidgetFromViewport_IfActive();
	St.Pop();
	AddTopWidgetToViewport_IfActive();
}

UUserWidget* UWidgetClassStack::TopWidget() const
{
	if( ! IsActive() )
	{
		return nullptr;
	}

	if( IsEmpty() )
	{
		return nullptr;
	}

	const FWidgetClassStack_ImplElem* const Elem = TopElem();
	return Elem->Widget;
}

const FWidgetClassStackElement& UWidgetClassStack::TopCreatorElement() const
{
	check( ! IsEmpty() );

	const FWidgetClassStack_ImplElem* Elem = TopElem();
	return Elem->CreatorElement;
}

void UWidgetClassStack::AddTopWidgetToViewport()
{
	if( IsEmpty() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping adding top widget: stack is empty"), *LogPrefix);
		return;
	}
	UE_LOG(MyLog, Log, TEXT("%s Create and add top widget"), *LogPrefix);
	CreateAndShowWidget(this, GetPC(), TopElem(), FName(TEXT("TopWidget")));
}

void UWidgetClassStack::RemoveTopWidgetFromViewport()
{
	if( IsEmpty() )
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping removing top widget: stack is empty"), *LogPrefix);
		return;
	}

	UE_LOG(MyLog, Log, TEXT("%s Removing top widget"), *LogPrefix);
	HideAndDestroyWidget_IfCreated(this, TopElem());
}

void UWidgetClassStack::AddTopWidgetToViewport_IfActive()
{
	if( IsActive() )
	{		
		AddTopWidgetToViewport();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping adding top widget - stack is inactive"), *LogPrefix);
	}
}

void UWidgetClassStack::RemoveTopWidgetFromViewport_IfActive()
{
	if( IsActive() )
	{
		RemoveTopWidgetFromViewport();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("%s Skipping removing top widget - stack is inactive"), *LogPrefix);
	}
}

const FWidgetClassStack_ImplElem* UWidgetClassStack::TopElem() const
{
	if( IsEmpty() )
	{
		return nullptr;
	}
	else
	{
		return &St.Top();
	}
}

FWidgetClassStack_ImplElem* UWidgetClassStack::TopElem()
{
	if( IsEmpty() )
	{
		return nullptr;
	}
	else
	{
		return &St.Top();
	}
}

APlayerController* UWidgetClassStack::GetPC() const
{
	check(PC);
	return PC;
}
