// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "BountyAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec,
	                   FActiveGameplayEffectHandle ActiveEffectHandle);
};
