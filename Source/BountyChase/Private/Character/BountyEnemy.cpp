// Copyright Dmytro Donets


#include "Character/BountyEnemy.h"

#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAttributeSet.h"

ABountyEnemy::ABountyEnemy()
{
	GetMesh()->SetCustomDepthStencilValue(250);
	Weapon->SetCustomDepthStencilValue(250);

	AbilitySystemComponent = CreateDefaultSubobject<UBountyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UBountyAttributeSet>("AttributeSet");
}

void ABountyEnemy::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void ABountyEnemy::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

void ABountyEnemy::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();
}

void ABountyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBountyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();
}
