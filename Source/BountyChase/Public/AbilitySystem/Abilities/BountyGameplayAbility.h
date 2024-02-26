// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "BountyGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

};
