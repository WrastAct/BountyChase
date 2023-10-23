// Copyright Dmytro Donets


#include "Character/BountyCharacterBase.h"

ABountyCharacterBase::ABountyCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

UAbilitySystemComponent* ABountyCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ABountyCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

void ABountyCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

