// Copyright Dmytro Donets


#include "Input/BountyInputConfig.h"

const UInputAction* UBountyInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag,
                                                                     bool bLogNotFound) const
{
	for (const FBountyInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"),
		       *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
