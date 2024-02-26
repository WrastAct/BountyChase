// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BountyDamageGameplayAbility.h"
#include "BountyProjectileSpell.generated.h"

class ABountyProjectile;
class UGameplayEffect;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyProjectileSpell : public UBountyDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo,
	                             const FGameplayEventData* TriggerEventData) override;
	
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABountyProjectile> ProjectileClass;
};
