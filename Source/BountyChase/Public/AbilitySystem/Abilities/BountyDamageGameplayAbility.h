// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BountyGameplayAbility.h"
#include "BountyDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyDamageGameplayAbility : public UBountyGameplayAbility
{
	GENERATED_BODY()
protected:
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
