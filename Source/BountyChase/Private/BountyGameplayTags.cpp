// Copyright Dmytro Donets


#include "BountyGameplayTags.h"
#include "GameplayTagsManager.h"

FBountyGameplayTags FBountyGameplayTags::GameplayTags;

void FBountyGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 * Primary Attributes
	 */
	
	GameplayTags.Attributes_Primary_Luck = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Luck"), FString("Defines how random events favor player"));
	GameplayTags.Attributes_Primary_Agility = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Agility"), FString("Defines how fast player is"));
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Strength"), FString("Defines how strong and enduring player is"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"), FString("Defines how strong player's spells are"));
	GameplayTags.Attributes_Primary_Darkness = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Darkness"), FString("Defines player's connection with Gods"));

	/*
	 * Secondary Attributes
	 **/
	
	GameplayTags.Attributes_Secondary_AttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackDamage"), FString("Attack damage amplification"));
	GameplayTags.Attributes_Secondary_SpellDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.SpellDamage"), FString("Spell damage amplification"));
	GameplayTags.Attributes_Secondary_CooldownReduction = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.CooldownReduction"), FString("Reduces spell cooldown"));
	GameplayTags.Attributes_Secondary_MovementSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MovementSpeed"), FString("How fast player moves"));
	GameplayTags.Attributes_Secondary_AttackSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.AttackSpeed"), FString("How fast player attacks"));
	GameplayTags.Attributes_Secondary_RollSpeed = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.RollSpeed"), FString("How fast player rolls"));
	GameplayTags.Attributes_Secondary_DodgeChance = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.DodgeChance"), FString("Chance to avoid damage"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxHealth"), FString("Maximum Health above which you cannot regenerate"));
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Secondary.MaxStamina"), FString("Maximum Stamina value above which you cannot regenerate"));

	/*
	 * Vital Attributes
	 */
	
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Health"), FString("When this reaches zero player dies"));
	GameplayTags.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Vital.Stamina"), FString("Used for different actions such as rolling"));

	/*
	 * Input Tags
	 */

	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.Q"), FString("Input Tag for Q key"));
	
	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.F"), FString("Input Tag for F key"));

	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage"),
		FString("Damage")
	);
	
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Physical"),
		FString("Physical Damage Type")
	);

	GameplayTags.Damage_Magical = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Damage.Magical"),
		FString("Magical Damage Type")
	);

	GameplayTags.DamageTypes.Add(GameplayTags.Damage_Physical);
	GameplayTags.DamageTypes.Add(GameplayTags.Damage_Magical);

	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Effects.HitReact"),
		FString("Tag granted when Hit Reacting")
	);
}
