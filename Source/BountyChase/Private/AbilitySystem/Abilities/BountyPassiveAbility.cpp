// Copyright Dmytro Donets


#include "AbilitySystem/Abilities/BountyPassiveAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/BountyAbilitySystemComponent.h"

class UBountyAbilitySystemComponent;

void UBountyPassiveAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (UBountyAbilitySystemComponent* BountyASC = Cast<UBountyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo())))
	{
		BountyASC->DeactivatePassiveAbility.AddUObject(this, &UBountyPassiveAbility::ReceiveDeactivate);
	}
}

void UBountyPassiveAbility::ReceiveDeactivate(const FGameplayTag& AbilityTag)
{
	if (AbilityTags.HasTagExact(AbilityTag))
	{
		EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, true);
	}
}
