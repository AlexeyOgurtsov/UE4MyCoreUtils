#include "ActorSelectorUIComponent.h"
#include "Util\Selection\IActorSelector.h"
#include "Util\Core\LogUtilLib.h"

#include "UObject/ConstructorHelpers.h"

UActorSelectorUIComponent::UActorSelectorUIComponent()
{
	const TCHAR* const WIDGET_RESOURCE_PATH = TEXT("WidgetBlueprint'/Game/Selection/UI/W_ActorSelectorWidget.W_ActorSelectorWidget_C'");
	ConstructorHelpers::FObjectFinderOptional<UClass> WidgetFinder{ WIDGET_RESOURCE_PATH };
	if (WidgetFinder.Succeeded())
	{
		WidgetClass = WidgetFinder.Get();
	}
	else
	{
		M_LOG_ERROR(TEXT("Unable to find widget class resource \"%s\""), WIDGET_RESOURCE_PATH);
	}
}

void UActorSelectorUIComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UActorSelectorUIComponent::InitAtControllerBeginPlay(const TScriptInterface<IActorSelector>& InActorSelector)
{
	if ( ! InitWidget() )
	{
		return;
	}
	SetActorSelector(InActorSelector);	
}

void UActorSelectorUIComponent::SetActorSelector(const TScriptInterface<IActorSelector>& InActorSelector)
{
	ActorSelector = InActorSelector;
	UpdateUI();
}

void UActorSelectorUIComponent::UpdateUI()
{
	Widget->ClearItems();
	for (const AActor* Actor : ActorSelector->GetActors())
	{
		Widget->AddItem(ActorToItem(Actor));
	}
	Widget->SetSelectedIndex(ActorSelector->GetSelectedIndex());
}

FActorSelectorWidgetItem UActorSelectorUIComponent::ActorToItem(const AActor* InActor) const
{
	return FActorSelectorWidgetItem(FText::FromString(InActor->GetName()), InActor);
}

bool UActorSelectorUIComponent::InitWidget()
{
	const auto PC = Cast<APlayerController>(GetOwner());
	checkf(PC, TEXT("The selector UI component must be created with PlayerController as owner only!"))

	Widget = CreateWidget<UActorSelectorWidgetBase>(PC, WidgetClass.Get());
	if (!IsValid(Widget))
	{
		M_LOG_ERROR(TEXT("Widget initialization failed"));
		return false;
	}

	if ( ! Widget->IsInViewport() )
	{
		Widget->AddToViewport();
	}

	return true;
}