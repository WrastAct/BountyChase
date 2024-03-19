// Copyright Dmytro Donets


#include "UI/WidgetController/BountyWidgetController.h"

#include "Player/BountyPlayerController.h"
#include "Player/BountyPlayerState.h"
#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"

void UBountyWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UBountyWidgetController::BroadcastInitialValues()
{
	
}

void UBountyWidgetController::BindCallbacksToDependencies()
{
	
}

void UBountyWidgetController::BroadcastAbilityInfo()
{
	if (!GetBountyASC()->bStartupAbilitiesGiven) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
	{
		FBountyAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(BountyAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
		Info.InputTag = BountyAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
		Info.StatusTag = BountyAbilitySystemComponent->GetStatusFromSpec(AbilitySpec);
		AbilityInfoDelegate.Broadcast(Info);
	});
	GetBountyASC()->ForEachAbility(BroadcastDelegate);
}

ABountyPlayerController* UBountyWidgetController::GetBountyPC()
{
	if (BountyPlayerController == nullptr)
	{
		BountyPlayerController = Cast<ABountyPlayerController>(PlayerController);
	}
	return BountyPlayerController;
}

ABountyPlayerState* UBountyWidgetController::GetBountyPS()
{
	if (BountyPlayerState == nullptr)
	{
		BountyPlayerState = Cast<ABountyPlayerState>(PlayerState);
	}
	return BountyPlayerState;
}

UBountyAbilitySystemComponent* UBountyWidgetController::GetBountyASC()
{
	if (BountyAbilitySystemComponent == nullptr)
	{
		BountyAbilitySystemComponent = Cast<UBountyAbilitySystemComponent>(AbilitySystemComponent);
	}
	return BountyAbilitySystemComponent;
}

UBountyAttributeSet* UBountyWidgetController::GetBountyAS()
{
	if (BountyAttributeSet == nullptr)
	{
		BountyAttributeSet = Cast<UBountyAttributeSet>(AttributeSet);
	}
	return BountyAttributeSet;
}
