// Copyright Dmytro Donets


#include "AbilitySystem/BountyAbilitySystemLibrary.h"

#include "BountyAbilityTypes.h"
#include "Game/BountyGameModeBase.h"
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

void UBountyAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	const ABountyGameModeBase* BountyGameMode = Cast<ABountyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (BountyGameMode == nullptr) return;
	
	const AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = BountyGameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UBountyAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	ABountyGameModeBase* BountyGameMode = Cast<ABountyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (BountyGameMode == nullptr) return;

	UCharacterClassInfo* CharacterClassInfo = BountyGameMode->CharacterClassInfo;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
}

UCharacterClassInfo* UBountyAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	ABountyGameModeBase* BountyGameMode = Cast<ABountyGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (BountyGameMode == nullptr) return nullptr;
	return BountyGameMode->CharacterClassInfo;
}

bool UBountyAbilitySystemLibrary::IsDodgedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FBountyGameplayEffectContext* BountyEffectContext = static_cast<const FBountyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return BountyEffectContext->IsDodgedHit();
	}
	return false;
}

void UBountyAbilitySystemLibrary::SetIsDodgedHit(FGameplayEffectContextHandle& EffectContextHandle, bool bInIsDodgedHit)
{
	if (FBountyGameplayEffectContext* BountyEffectContext = static_cast<FBountyGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		BountyEffectContext->SetIsDodgedHit(bInIsDodgedHit);
	}
}
