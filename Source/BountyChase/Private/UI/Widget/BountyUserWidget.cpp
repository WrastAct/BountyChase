// Copyright Dmytro Donets


#include "UI/Widget/BountyUserWidget.h"

void UBountyUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
