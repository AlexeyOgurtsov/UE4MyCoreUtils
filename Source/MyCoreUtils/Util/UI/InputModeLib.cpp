#include "InputModeLib.h"
#include "UIUtilLib.h"
#include "Blueprint/UserWidget.h"

FInputModeStackElement FInputModeStackElement::CreateGameOnly()
{
	FInputModeGameOnly M;
	return FInputModeStackElement { M };
}

FInputModeStackElement FInputModeStackElement::CreateUIOnly(UUserWidget* InWidgetToFocus)
{
	FInputModeUIOnly M;
	M.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	M.SetWidgetToFocus(InWidgetToFocus->TakeWidget());
	return FInputModeStackElement { M };
}

FInputModeStackElement FInputModeStackElement::CreateGameAndUI(UUserWidget* InWidgetToFocus)
{
	FInputModeGameAndUI M;
	M.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	M.SetWidgetToFocus(InWidgetToFocus->TakeWidget());
	return FInputModeStackElement { M };
}

TSharedPtr<SWidget> FInputModeStackElement::GetWidgetToFocus() const
{
	switch(GetInputModeType())
	{
	case EInputModeType::IM_UI:
		return FInputModeUIOnly_AccessHelper{GetUI()}.GetWidgetToFocus();

	case EInputModeType::IM_Game:
		break;

	case EInputModeType::IM_GameAndUI:
		return FInputModeGameAndUI_AccessHelper{GetGameAndUI()}.GetWidgetToFocus();

	default:
		break;
	}
	checkNoEntry();
	return nullptr;
}

FString UInputModeLib::InputModeTypeToString(EInputModeType InInputMode)
{
	switch(InInputMode)
	{
	case EInputModeType::IM_UI:
		return FString(TEXT("UI"));

	case EInputModeType::IM_Game:
		return FString(TEXT("Game"));

	case EInputModeType::IM_GameAndUI:
		return FString(TEXT("GameAndUI"));

	default:
		break;
	}
	checkNoEntry();
	return FString(TEXT("{Unknown EInputModeType}"));
}

FString UInputModeLib::InputModeToString(const FInputModeStackElement& InElement)
{
	FString const InputModeTypeString = InputModeTypeToString(InElement.GetInputModeType());
	FString ResultString = FString::Printf(TEXT("{Type=%s"), *InputModeTypeString);


	FString WidgetToFocusString;
	if
	(
		InElement.GetInputModeType() == EInputModeType::IM_UI
		|| InElement.GetInputModeType() == EInputModeType::IM_GameAndUI
	)
	{
		WidgetToFocusString = FString::Printf(TEXT("WidgetToFocus=\"%s\""), (InElement.GetWidgetToFocus() ? TEXT("SET") : TEXT("nullptr")));
	}

	switch(InElement.GetInputModeType())
	{
	case EInputModeType::IM_UI:
		ResultString.Append(TEXT("; "));
		ResultString.Append(*WidgetToFocusString);
		break;

	case EInputModeType::IM_Game:
		break;

	case EInputModeType::IM_GameAndUI:
		ResultString.Append(TEXT("; "));
		ResultString.Append(*WidgetToFocusString);
		break;

	default:
		checkNoEntry();
	}
	ResultString.AppendChar(TCHAR('}'));
	return ResultString;
}

void UInputModeLib::SetInputMode(APlayerController* InPC, const FInputModeStackElement& InElement)
{
	check(InPC);

	switch(InElement.GetInputModeType())
	{
	case EInputModeType::IM_UI:
		InPC->SetInputMode(InElement.GetUI());
		return;

	case EInputModeType::IM_Game:
		InPC->SetInputMode(InElement.GetGame());
		return;

	case EInputModeType::IM_GameAndUI:
		InPC->SetInputMode(InElement.GetGameAndUI());
		return;

	default:
		break;
	}
	checkNoEntry();
}