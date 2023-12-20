// Copyright Dmytro Donets


#include "AbilitySystem/BountyAbilitySystemLibrary.h"

#include "Kismet/GameplayStatics.h"
#include "UI/WidgetController/BountyWidgetController.h"
#include "Player/BountyPlayerState.h"
#include "UI/HUD/BountyHUD.h"

UOverlayWidgetController* UBountyAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ABountyHUD* BountyHUD = Cast<ABountyHUD>(PC->GetHUD()))
		{
			ABountyPlayerState* PS = PC->GetPlayerState<ABountyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return BountyHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}

UAttributeMenuWidgetController* UBountyAbilitySystemLibrary::GetAttributeMenuWidgetController(
	const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ABountyHUD* BountyHUD = Cast<ABountyHUD>(PC->GetHUD()))
		{
			ABountyPlayerState* PS = PC->GetPlayerState<ABountyPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return BountyHUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
	}

	return nullptr;
}
