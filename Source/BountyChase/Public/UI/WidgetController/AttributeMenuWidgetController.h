// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/BountyWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class BOUNTYCHASE_API UAttributeMenuWidgetController : public UBountyWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnLuckChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnAgilityChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnStrengthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnIntelligenceChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Primary Attributes")
	FOnAttributeChangedSignature OnDarknessChanged;


	
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnAttackDamageChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnSpellDamageChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnCooldownReductionChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnMovementSpeedChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnAttackSpeedChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnRollSpeedChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnDodgeChanceChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Secondary Attributes")
	FOnAttributeChangedSignature OnMaxStaminaChanged;

	

	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Vital Attributes")
	FOnAttributeChangedSignature OnStaminaChanged;
};
