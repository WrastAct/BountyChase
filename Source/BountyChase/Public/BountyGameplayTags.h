// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * 
 */

struct FBountyGameplayTags
{
public:
	static const FBountyGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Luck;
	FGameplayTag Attributes_Primary_Agility;
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Darkness;
	
	FGameplayTag Attributes_Secondary_AttackDamage;
	FGameplayTag Attributes_Secondary_SpellDamage;
	FGameplayTag Attributes_Secondary_CooldownReduction;
	FGameplayTag Attributes_Secondary_MovementSpeed;
	FGameplayTag Attributes_Secondary_AttackSpeed;
	FGameplayTag Attributes_Secondary_RollSpeed;
	FGameplayTag Attributes_Secondary_DodgeChance;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxStamina;
	
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Stamina;
protected:

private:
    static FBountyGameplayTags GameplayTags;
};
