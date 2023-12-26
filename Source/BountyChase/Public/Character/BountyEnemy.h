// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Character/BountyCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "BountyEnemy.generated.h"

class UWidgetComponent;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyEnemy : public ABountyCharacterBase, public IEnemyInterface, public IHighlightInterface
{
	GENERATED_BODY()
public:
	ABountyEnemy();

	//~ Begin IHighlightInterface
	virtual void HighlightActor_Implementation() override;
	virtual void UnHighlightActor_Implementation() override;
	//~ End IHighlightInterface

	/* Begin Combat Interface */
	virtual void SetCombatTarget_Implementation(AActor* InCombatTarget) override;
	virtual AActor* GetCombatTarget_Implementation() const override;
	/* End Combat Interface*/
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	TObjectPtr<AActor> CombatTarget;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;
};
