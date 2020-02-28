#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Templates/SubclassOf.h"
#include "WidgetClassStackLib.generated.h"

class UUserWidget;
class APlayerController;

UENUM(BlueprintType)
enum class EWidgetStackElementType : uint8
{
	WidgetClass UMETA(DisplayName = "WidgetClass"),
	NUM UMETA(Hidden)
};

USTRUCT(BlueprintType)
struct FWidgetClassStackElement
{
	GENERATED_BODY()	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Widget)
	TSubclassOf<UUserWidget> WidgetClass;

	EWidgetStackElementType GetElementType() const;

	FWidgetClassStackElement() = default;
	FWidgetClassStackElement(TSubclassOf<UUserWidget> InWidgetClass);
};

UCLASS()
class UWidgetClassStackLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Widgets")
	static UUserWidget* CreateWidget(APlayerController* InPC, const FWidgetClassStackElement& InElement);
};