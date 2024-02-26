// Copyright Dmytro Donets


#include "AbilitySystem/BountyAbilitySystemGlobals.h"

#include "BountyAbilityTypes.h"

FGameplayEffectContext* UBountyAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FBountyGameplayEffectContext();
}