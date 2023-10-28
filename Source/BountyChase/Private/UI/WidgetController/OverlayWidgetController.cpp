// Copyright Dmytro Donets


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BountyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(BountyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BountyAttributeSet->GetMaxHealth());
}
