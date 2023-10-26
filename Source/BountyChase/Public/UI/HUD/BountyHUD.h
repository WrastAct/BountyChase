// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BountyHUD.generated.h"

class UBountyUserWidget;
/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TObjectPtr<UBountyUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UBountyUserWidget> OverlayWidgetClass;
};
