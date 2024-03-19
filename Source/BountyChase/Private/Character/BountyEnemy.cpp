// Copyright Dmytro Donets


#include "Character/BountyEnemy.h"

#include "BountyGameplayTags.h"
#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAbilitySystemLibrary.h"
#include "AbilitySystem/BountyAttributeSet.h"
#include "BountyChase/BountyChase.h"
#include "Components/WidgetComponent.h"
#include "AI/BountyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/BountyUserWidget.h"

ABountyEnemy::ABountyEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UBountyAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	AttributeSet = CreateDefaultSubobject<UBountyAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	Weapon->MarkRenderStateDirty();
}

void ABountyEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	BountyAIController = Cast<ABountyAIController>(NewController);
	BountyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	BountyAIController->RunBehaviorTree(BehaviorTree);
	BountyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	BountyAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"),
	                                                             CharacterClass != ECharacterClass::Warrior);
}

void ABountyEnemy::HighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(true);
	Weapon->SetRenderCustomDepth(true);
}

void ABountyEnemy::UnHighlightActor_Implementation()
{
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}

int32 ABountyEnemy::GetPlayerLevel_Implementation()
{
	return Level;
}

void ABountyEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ABountyEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ABountyEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	if (BountyAIController) BountyAIController->GetBlackboardComponent()->SetValueAsBool(FName("Dead"), true);
	
	Super::Die();
}

void ABountyEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (BountyAIController && BountyAIController->GetBlackboardComponent())
	{
		BountyAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}

void ABountyEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		UBountyAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}

	if (UBountyUserWidget* BountyUserWidget = Cast<UBountyUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		BountyUserWidget->SetWidgetController(this);
	}

	if (const UBountyAttributeSet* BountyAS = Cast<UBountyAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(BountyAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->RegisterGameplayTagEvent(FBountyGameplayTags::Get().Effects_HitReact,
		                                                 EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&ABountyEnemy::HitReactTagChanged
		);

		OnHealthChanged.Broadcast(BountyAS->GetHealth());
		OnMaxHealthChanged.Broadcast(BountyAS->GetMaxHealth());
	}
}

void ABountyEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	Cast<UBountyAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	if (HasAuthority())
	{
		InitializeDefaultAttributes();
	}
}

void ABountyEnemy::InitializeDefaultAttributes() const
{
	UBountyAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, Level, AbilitySystemComponent);
}
