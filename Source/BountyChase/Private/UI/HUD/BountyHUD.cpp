// Copyright Dmytro Donets


#include "UI/HUD/BountyHUD.h"

#include "UI/Widget/BountyUserWidget.h"

void ABountyHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
