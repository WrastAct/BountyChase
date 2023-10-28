// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BountyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
};
