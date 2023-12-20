// Copyright Dmytro Donets


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAttributeSet.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);

	OnLuckChanged.Broadcast(BountyAttributeSet->GetLuck());
	OnAgilityChanged.Broadcast(BountyAttributeSet->GetAgility());
	OnStrengthChanged.Broadcast(BountyAttributeSet->GetStrength());
	OnIntelligenceChanged.Broadcast(BountyAttributeSet->GetIntelligence());
	OnDarknessChanged.Broadcast(BountyAttributeSet->GetDarkness());
	
	OnAttackDamageChanged.Broadcast(BountyAttributeSet->GetAttackDamage());
	OnSpellDamageChanged.Broadcast(BountyAttributeSet->GetSpellDamage());
	OnCooldownReductionChanged.Broadcast(BountyAttributeSet->GetCooldownReduction());
	OnMovementSpeedChanged.Broadcast(BountyAttributeSet->GetMovementSpeed());
	OnAttackSpeedChanged.Broadcast(BountyAttributeSet->GetAttackSpeed());
	OnRollSpeedChanged.Broadcast(BountyAttributeSet->GetRollSpeed());
	OnDodgeChanceChanged.Broadcast(BountyAttributeSet->GetDodgeChance());
	OnMaxHealthChanged.Broadcast(BountyAttributeSet->GetMaxHealth());
	OnMaxStaminaChanged.Broadcast(BountyAttributeSet->GetMaxStamina());
	
	OnHealthChanged.Broadcast(BountyAttributeSet->GetHealth());
	OnStaminaChanged.Broadcast(BountyAttributeSet->GetStamina());
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UBountyAttributeSet* BountyAttributeSet = CastChecked<UBountyAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetLuckAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnLuckChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetAgilityAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnAgilityChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetStrengthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStrengthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetIntelligenceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnIntelligenceChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetDarknessAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnDarknessChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetAttackDamageAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnAttackDamageChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetSpellDamageAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnSpellDamageChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetCooldownReductionAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnCooldownReductionChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetMovementSpeedAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMovementSpeedChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetAttackSpeedAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnAttackSpeedChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetRollSpeedAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnRollSpeedChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetDodgeChanceAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnDodgeChanceChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetMaxStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxStaminaChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetStaminaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnStaminaChanged.Broadcast(Data.NewValue);
		}
	);

}