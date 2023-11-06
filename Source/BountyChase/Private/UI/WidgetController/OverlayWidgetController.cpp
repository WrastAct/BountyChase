// Copyright Dmytro Donets


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BountyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(BountyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BountyAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetHealthAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::HealthChanged);	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetMaxHealthAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
