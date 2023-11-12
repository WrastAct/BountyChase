// Copyright Dmytro Donets


#include "AbilitySystem/ModMagCalc/MMC_MaxHealth.h"

#include "AbilitySystem/BountyAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	StrengthDef.AttributeToCapture = UBountyAttributeSet::GetStrengthAttribute();
	StrengthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	StrengthDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(StrengthDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Strength = 0.f;
	GetCapturedAttributeMagnitude(StrengthDef, Spec, EvaluationParameters, Strength);
	Strength = FMath::Max<float>(Strength, 0.f);
	
	return 100.f + 15.f * Strength;
}
