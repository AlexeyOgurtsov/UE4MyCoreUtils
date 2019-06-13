#pragma once

#include "GameFramework/PlayerController.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "InputModeLib.generated.h"

class UUserWidget;

UENUM(BlueprintType)
enum class EInputModeType : uint8
{
	IM_UI UMETA(DisplayName="UI"),
	IM_Game UMETA(DisplayName="Game"),
	IM_GameAndUI UMETA(DisplayName="GameAndUI")
};

/**
* Hack for accessing Widget-to-focus.
*/
struct FInputModeUIOnly_AccessHelper : public FInputModeUIOnly
{
	FInputModeUIOnly_AccessHelper(const FInputModeUIOnly& InMode) :
		FInputModeUIOnly{InMode}
	{
	}

	TSharedPtr<SWidget> GetWidgetToFocus() const { return WidgetToFocus; }
};

/**
* Hack for accessing Widget-to-focus.
*/
struct FInputModeGameAndUI_AccessHelper : public FInputModeGameAndUI
{
	FInputModeGameAndUI_AccessHelper(const FInputModeGameAndUI& InMode) :
		FInputModeGameAndUI{InMode}
	{
	}

	TSharedPtr<SWidget> GetWidgetToFocus() const { return WidgetToFocus; }
};

USTRUCT()
struct FInputModeStackElement
{
	GENERATED_BODY()

	EInputModeType GetInputModeType() const { return InputModeType; }

	TSharedPtr<SWidget> GetWidgetToFocus() const;

	const FInputModeGameOnly& GetGame() const 
	{
		checkf(InputModeType == EInputModeType::IM_Game, TEXT("FInputModeStackElement::GetInputModeGameOnly: wrong input mode"));
		return Game;
	}

	const FInputModeUIOnly& GetUI() const 
	{
		checkf(InputModeType == EInputModeType::IM_UI, TEXT("FInputModeStackElement::GetInputModeUIOnly: wrong input mode"));
		return UI;
	}

	const FInputModeGameAndUI& GetGameAndUI() const 
	{
		checkf(InputModeType == EInputModeType::IM_GameAndUI, TEXT("FInputModeStackElement::GetInputModeGameAndUI: wrong input mode"));
		return GameAndUI;
	}

public:
	FInputModeStackElement() {}
	FInputModeStackElement(FInputModeUIOnly InUI) 
	:	InputModeType(EInputModeType::IM_UI)
	,	UI(InUI) 
	{
		FInputModeUIOnly_AccessHelper M {InUI};
		WidgetToFocus = M.GetWidgetToFocus();
	}
	FInputModeStackElement(FInputModeGameOnly InGame) :
		InputModeType(EInputModeType::IM_Game)
	,	Game(InGame) 
	{
		WidgetToFocus = nullptr;
	}
	FInputModeStackElement(FInputModeGameAndUI InGameAndUI) :
		InputModeType(EInputModeType::IM_GameAndUI)
	,	GameAndUI(InGameAndUI) 
	{
		FInputModeGameAndUI_AccessHelper M {InGameAndUI};
		WidgetToFocus = M.GetWidgetToFocus();
	}

	static FInputModeStackElement CreateGameOnly();
	static FInputModeStackElement CreateUIOnly(UUserWidget* InWidgetToFocus);
	static FInputModeStackElement CreateGameAndUI(UUserWidget* InWidgetToFocus);

private:
	EInputModeType InputModeType;
	FInputModeUIOnly UI;
	FInputModeGameOnly Game;
	FInputModeGameAndUI GameAndUI;

	/**
	* We need this property to keep the widget to be garbage collected, because the FInputMode* structures do NOT do it.
	*/
	TSharedPtr<SWidget> WidgetToFocus = nullptr;
};


UCLASS()
class UInputModeLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static FString InputModeTypeToString(EInputModeType InInputMode);
	static FString InputModeToString(const FInputModeStackElement& InElement);
	static void SetInputMode(APlayerController* InPC, const FInputModeStackElement& InElement);	
};