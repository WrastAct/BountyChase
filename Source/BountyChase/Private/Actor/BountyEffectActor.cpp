// Copyright Dmytro Donets


#include "Actor/BountyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/BountyAttributeSet.h"
#include "Components/SphereComponent.h"

ABountyEffectActor::ABountyEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	Sphere->SetupAttachment(GetRootComponent());
}

void ABountyEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: apply effect instead
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UBountyAttributeSet* BountyAttributeSet = Cast<UBountyAttributeSet>(
			ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UBountyAttributeSet::StaticClass()));

		UBountyAttributeSet* MutableBountyAttributeSet = const_cast<UBountyAttributeSet*>(BountyAttributeSet);
		MutableBountyAttributeSet->SetHealth(BountyAttributeSet->GetHealth() + 10.f);

		Destroy();
	}
}

void ABountyEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ABountyEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &ABountyEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &ABountyEffectActor::EndOverlap);
}

