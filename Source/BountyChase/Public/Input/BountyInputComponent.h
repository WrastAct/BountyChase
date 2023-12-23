// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "BountyInputConfig.h"
#include "BountyInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const UBountyInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc,
	                        ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
};



template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UBountyInputComponent::BindAbilityActions(const UBountyInputConfig* InputConfig, UserClass* Object,
                                               PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc,
                                               HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FBountyInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}
		}
	}
};
