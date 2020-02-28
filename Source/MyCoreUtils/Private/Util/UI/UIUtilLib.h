#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Blueprint/UserWidget.h"
#include "UIUtilLib.generated.h"

class UUserWidget;

UCLASS()
class UUIUtilLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UUIUtilLib();

	UFUNCTION(BlueprintCallable, Category = Input)
	static void SetInputMode_GameAndUI(APlayerController* PC, UUserWidget* InWidget);

	UFUNCTION(BlueprintCallable, Category = Input)
	static void SetInputMode_GameOnly(APlayerController* PC);

	UFUNCTION(BlueprintCallable, Category = Input)
	static void SetInputMode_UIOnly(APlayerController* PC, UUserWidget* InWidget);

	/**
	* Logged version of CreateWidget.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	static UUserWidget* CreateWidget(APlayerController* InPC, TSubclassOf<UUserWidget> InWidgetClass);

	/**
	* Shows widget but only if it's not in viewport already.
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	static void ShowWidget(UUserWidget* InWidget);

	/**
	* Hides widget but only if it's not hidden yet
	*/
	UFUNCTION(BlueprintCallable, Category = Widgets)
	static void HideWidget(UUserWidget* InWidget);
};