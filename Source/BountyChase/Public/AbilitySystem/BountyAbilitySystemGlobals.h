// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "BountyAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
};
