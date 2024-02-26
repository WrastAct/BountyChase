// Copyright Dmytro Donets


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AbilitySystemComponent.h"
#include "BountyGameplayTags.h"
#include "BountyAbilityTypes.h"
#include "AbilitySystem/BountyAbilitySystemLibrary.h"
#include "AbilitySystem/BountyAttributeSet.h"

struct BountyDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DodgeChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SpellDamage);

	BountyDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBountyAttributeSet, DodgeChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UBountyAttributeSet, SpellDamage, Source, false);
	}
};

static const BountyDamageStatics& DamageStatics()
{
	static BountyDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().DodgeChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().SpellDamageDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.f;
	for (FGameplayTag DamageTypeTag : FBountyGameplayTags::Get().DamageTypes)
	{
		const float DamageTypeValue = Spec.GetSetByCallerMagnitude(DamageTypeTag);
		Damage += DamageTypeValue;
	}
	
	float TargetDodgeChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DodgeChanceDef, EvaluationParameters, TargetDodgeChance);
	TargetDodgeChance = FMath::Max<float>(TargetDodgeChance, 0.f);
	
	const bool bDodged = FMath::RandRange(1, 100) < TargetDodgeChance;

	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	UBountyAbilitySystemLibrary::SetIsDodgedHit(EffectContextHandle, bDodged);
	
	Damage = bDodged ? 0 : Damage;

	float SourceSpellDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().SpellDamageDef, EvaluationParameters, SourceSpellDamage);
	SourceSpellDamage = FMath::Max<float>(SourceSpellDamage, 0.f);

	Damage *= 1 + SourceSpellDamage;

	const FGameplayModifierEvaluatedData EvaluatedData(UBountyAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
