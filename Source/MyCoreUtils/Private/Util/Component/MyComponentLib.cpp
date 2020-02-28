#include "MyComponentLib.h"
#include "IMyComponent.h"

#include "../Core/LogUtilLib.h"

#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"

class MyComponentLoop
{
public:
	MyComponentLoop(AActor* InOwner)
	{
		check(InOwner);
		TheOwner = InOwner;
	}

	void Run();

protected:
	AActor* GetTheOwner() const { return TheOwner; }

	virtual void DoComponent(UActorComponent* InCompObject, IMyComponent* InComp) = 0;

private:
	AActor* TheOwner = nullptr;
};

class MyComponentLoop_CallBindOwner : public MyComponentLoop
{
public:
	MyComponentLoop_CallBindOwner(AActor* InOwner) :
		MyComponentLoop{InOwner}
	{
	}

protected:
	virtual void DoComponent(UActorComponent* InCompObject, IMyComponent* InComp) override	
	{
		IMyComponent::Execute_BindOwner(InCompObject, GetTheOwner());
	}
};

class MyComponentLoop_NotifyOwnerReady : public MyComponentLoop
{
public:
	MyComponentLoop_NotifyOwnerReady (AActor* InOwner) :
		MyComponentLoop{InOwner}
	{
	}

protected:
	virtual void DoComponent(UActorComponent* InCompObject, IMyComponent* InComp) override	
	{
		IMyComponent::Execute_OwnerReady(InCompObject, GetTheOwner());
	}
};


void UMyComponentLib::BindAllComponentsToOwner(AActor* InOwner)
{
	UE_LOG(MyLog, Log, TEXT("UMyComponentLib::BindAllComponentsToOwner..."));
	MyComponentLoop_CallBindOwner Loop{InOwner};
	Loop.Run();
	UE_LOG(MyLog, Log, TEXT("UMyComponentLib::BindAllComponentsToOwner DONE"));
}

void UMyComponentLib::NotifyOwnerReady(AActor* InOwner)
{
	UE_LOG(MyLog, Log, TEXT("UMyComponentLib::NotifyOwnerReady..."));
	MyComponentLoop_NotifyOwnerReady Loop{InOwner};
	Loop.Run();
	UE_LOG(MyLog, Log, TEXT("UMyComponentLib::NotifyOwnerReady DONE"));
}

void MyComponentLoop::Run()
{	
	int32 Index = 0;
	for(UActorComponent* Comp : TheOwner->GetComponents())
	{
		if(Comp)
		{
			UE_LOG(MyLog, Log, TEXT("Comp %d: named \"%s\" of class \"%s\""), Index, *Comp->GetName(), *Comp->GetClass()->GetName());
			if(auto MyComp = Cast<IMyComponent>(Comp))
			{
				UE_LOG(MyLog, Log, TEXT("IMyComponent interface supported"));
				DoComponent(Comp, MyComp);				
			}	
			else
			{
				UE_LOG(MyLog, Log, TEXT("Skipping component - IMyComponent interface NOT supported"));
			}
		}	
		else
		{
			UE_LOG(MyLog, Log, TEXT("Skipping nullptr component"));
		}
		++Index;
	}
}