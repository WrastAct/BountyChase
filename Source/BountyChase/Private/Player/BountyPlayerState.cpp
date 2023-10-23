// Copyright Dmytro Donets


#include "Player/BountyPlayerState.h"

#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAttributeSet.h"

ABountyPlayerState::ABountyPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBountyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UBountyAttributeSet>("AttributeSet");
	
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* ABountyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABountyPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
