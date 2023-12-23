// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataCharacterRotation.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCharacterRotationDataSignature, const FGameplayAbilityActorInfo&, DataHandle);

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UTargetDataCharacterRotation : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="Ability|Tasks", meta = (DisplayName = "TargetDataCharacterRotation", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UTargetDataCharacterRotation* CreateTargetDataCharacterRotation(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FCharacterRotationDataSignature ValidData;

private:

	virtual void Activate() override;
	void SendCharacterRotationData();
};
