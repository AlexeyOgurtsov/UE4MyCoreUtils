#include "UIUtilLib.h"
#include "Blueprint/UserWidget.h"
#include "Util/Core/LogUtilLib.h"

UUIUtilLib::UUIUtilLib()
{
}

void UUIUtilLib::SetInputMode_GameAndUI(APlayerController* PC, UUserWidget* InWidget)
{
	check(PC);

	FInputModeGameAndUI Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetWidgetToFocus(InWidget->TakeWidget());
	PC->SetInputMode(Mode);
}

void UUIUtilLib::SetInputMode_GameOnly(APlayerController* PC)
{
	check(PC);

	FInputModeGameOnly Mode;
	PC->SetInputMode(Mode);
}

void UUIUtilLib::SetInputMode_UIOnly(APlayerController* PC, UUserWidget* InWidget)
{	
	check(PC);

	FInputModeUIOnly Mode;
	Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	Mode.SetWidgetToFocus(InWidget->TakeWidget());
	PC->SetInputMode(Mode);
}

UUserWidget* UUIUtilLib::CreateWidget(APlayerController* InPC, TSubclassOf<UUserWidget> InWidgetClass)
{
	FString FunctionPrefix { TEXT("UUIUtilLib::CreateWidget:") };

	UE_LOG(MyLog, Log, TEXT("%s..."), *FunctionPrefix);
	check(InPC);

	if(InWidgetClass == nullptr)
	{
		UE_LOG(MyLog, Warning, TEXT("%s Skipping widget creation: Widget Class: nullptr"), *FunctionPrefix);
		return nullptr;	
	}
	else
	{
		//if(AreGameWidgetsRelevant())
		//{
			UE_LOG(MyLog, Log, TEXT("%s Class Name: %s"), *FunctionPrefix, *InWidgetClass->GetName());
			UUserWidget* W = ::CreateWidget(InPC, InWidgetClass);
			if(nullptr == W)
			{
				UE_LOG(MyLog, Warning, TEXT("%s CreateWidget returned nullptr!"), *FunctionPrefix);
				return nullptr;
			}
			return W;
		//}
		//else
		//{
		//	UE_LOG(MyLog, Log, TEXT("%s Skipping widget creation - irrelevant for current world"), *FunctionPrefix);
		//	return nullptr;
		//}
	}
}

void UUIUtilLib::ShowWidget(UUserWidget* InWidget)
{
	check(InWidget);

	if( ! InWidget->IsInViewport() )
	{
		InWidget->AddToViewport();
	}
	else
	{
		UE_LOG(MyLog, Log, TEXT("Widget \"%s\" of class \"%s\"is already in viewport"), *InWidget->GetName(), *InWidget->GetClass()->GetName());
	}
}

void UUIUtilLib::HideWidget(UUserWidget* InWidget)
{
	check(InWidget);

	if(InWidget->IsInViewport())	
	{
		InWidget->RemoveFromViewport();
	}
}