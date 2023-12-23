// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "BountyInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FBountyInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FBountyInputAction> AbilityInputActions;
};
