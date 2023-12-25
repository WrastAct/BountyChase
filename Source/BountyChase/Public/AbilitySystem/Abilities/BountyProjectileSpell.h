// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BountyGameplayAbility.h"
#include "BountyProjectileSpell.generated.h"

class ABountyProjectile;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyProjectileSpell : public UBountyGameplayAbility
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
