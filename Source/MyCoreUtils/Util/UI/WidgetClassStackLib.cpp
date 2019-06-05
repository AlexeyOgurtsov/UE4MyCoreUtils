#include "WidgetClassStackLib.h"
#include "Util/UI/UIUtilLib.h"
#include "../Core/LogUtilLib.h"

EWidgetStackElementType FWidgetClassStackElement::GetElementType() const	
{
	if(WidgetClass) 
	{
		return EWidgetStackElementType::WidgetClass;
	}
	checkNoEntry();
	return EWidgetStackElementType::NUM;
}

FWidgetClassStackElement::FWidgetClassStackElement(TSubclassOf<UUserWidget> InWidgetClass) :
	WidgetClass(InWidgetClass)
{
	check(InWidgetClass);
}

UUserWidget* UWidgetClassStackLib::CreateWidget(APlayerController* InPC, const FWidgetClassStackElement& InElement)
{
	UE_LOG(MyLog, Log, TEXT("UWidgetClassStackLib::CreateWidget..."));
	switch(InElement.GetElementType())
	{
	case EWidgetStackElementType::WidgetClass:
		return UUIUtilLib::CreateWidget(InPC, InElement.WidgetClass);

	default:
		checkNoEntry();
		return nullptr;
	}
}