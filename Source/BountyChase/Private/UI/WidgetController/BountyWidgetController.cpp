// Copyright Dmytro Donets


#include "UI/WidgetController/BountyWidgetController.h"

void UBountyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UBountyWidgetController::BroadcastInitialValues()
{
	
}
