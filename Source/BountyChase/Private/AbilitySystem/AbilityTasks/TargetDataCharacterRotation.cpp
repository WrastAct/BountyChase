// Copyright Dmytro Donets


#include "AbilitySystem/AbilityTasks/TargetDataCharacterRotation.h"

#include "AbilitySystemComponent.h"

UTargetDataCharacterRotation* UTargetDataCharacterRotation::CreateTargetDataCharacterRotation(
	UGameplayAbility* OwningAbility)
{
	UTargetDataCharacterRotation* MyObj = NewAbilityTask<UTargetDataCharacterRotation>(OwningAbility);
	return MyObj;
}

void UTargetDataCharacterRotation::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendCharacterRotationData();
	}
	else
	{
		//TODO: We are on the server, so listen for target data.
	}
}

void UTargetDataCharacterRotation::SendCharacterRotationData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();

	AActor* OwnerActor = Ability->GetCurrentActorInfo()->AbilitySystemComponent->GetOwnerActor();
	AActor* AvatarActor = Ability->GetCurrentActorInfo()->AbilitySystemComponent->GetAvatarActor();
	UAbilitySystemComponent* ASC = AbilitySystemComponent.Get();
	
	FGameplayAbilityActorInfo* Data = new FGameplayAbilityActorInfo();
	Data->InitFromActor(OwnerActor, AvatarActor, ASC);

	/*
	AbilitySystemComponent->ServerSetReplicatedTargetData()
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		Data,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);*/

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(*Data);
	}
	//
	// APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	// const FRotator CharacterRotator = PC->GetControlRotation();
}
