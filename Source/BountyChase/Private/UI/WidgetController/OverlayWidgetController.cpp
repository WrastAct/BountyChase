// Copyright Dmytro Donets


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/BountyAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(BountyAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(BountyAttributeSet->GetMaxHealth());
	OnStaminaChanged.Broadcast(BountyAttributeSet->GetStamina());
	OnMaxStaminaChanged.Broadcast(BountyAttributeSet->GetMaxStamina());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetHealthAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::HealthChanged);	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetMaxHealthAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetStaminaAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::StaminaChanged);	

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAttributeSet->GetMaxStaminaAttribute()).
	                        AddUObject(this, &UOverlayWidgetController::MaxStaminaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::StaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnStaminaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxStaminaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxStaminaChanged.Broadcast(Data.NewValue);
}
