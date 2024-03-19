// Copyright Dmytro Donets


#include "..\..\Public\Character\BountyCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "AbilitySystem/BountyAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BountyPlayerController.h"
#include "Player/BountyPlayerState.h"
#include "UI/HUD/BountyHUD.h"

ABountyCharacter::ABountyCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CharacterClass = ECharacterClass::Mage;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = RotationRate;
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;
	// CameraBoom->TargetArmLength = 400.f;	
	// CameraBoom->bUsePawnControlRotation = false;

	TopDownCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	TopDownCamera->bUsePawnControlRotation = false;
}

void ABountyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ABountyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client
	InitAbilityActorInfo();
}

int32 ABountyCharacter::GetSpellPoints_Implementation() const
{
	ABountyPlayerState* BountyPlayerState = GetPlayerState<ABountyPlayerState>();
	check(BountyPlayerState);
	return BountyPlayerState->GetSpellPoints();
}

int32 ABountyCharacter::GetSpellPointsReward_Implementation(int32 Level) const
{
	return Level;
}

void ABountyCharacter::AddToSpellPoints_Implementation(int32 InSpellPoints)
{
	ABountyPlayerState* BountyPlayerState = GetPlayerState<ABountyPlayerState>();
	check(BountyPlayerState);
	BountyPlayerState->AddToSpellPoints(InSpellPoints);

	if (UBountyAbilitySystemComponent* BountyASC = Cast<UBountyAbilitySystemComponent>(GetAbilitySystemComponent()))
	{
		BountyASC->UpdateAbilityStatuses(BountyPlayerState->GetSpellPoints());
	}
}

int32 ABountyCharacter::GetPlayerLevel_Implementation()
{
	return 1;
}

void ABountyCharacter::InitAbilityActorInfo()
{
	ABountyPlayerState* BountyPlayerState = GetPlayerState<ABountyPlayerState>();
	check(BountyPlayerState);
	BountyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BountyPlayerState, this);
	Cast<UBountyAbilitySystemComponent>(BountyPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = BountyPlayerState->GetAbilitySystemComponent();
	AttributeSet = BountyPlayerState->GetAttributeSet();

	// TODO: Implement in its own function in base class
	// Might be not the most suitable place for character movement manipulation
	// Should be implemented in base class because enemies should be affected too
	// Might be manipulated in Attribute Set via PostAttributeChange, but it feels odd to change Movement Component
	// of  characters outside of characters themselves
	const UBountyAttributeSet* BountyAttributeSet = Cast<UBountyAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		BountyAttributeSet->GetMovementSpeedAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				GetCharacterMovement()->MaxWalkSpeed = Data.NewValue;	
			}
	);

	if (ABountyPlayerController* BountyPlayerController = Cast<ABountyPlayerController>(GetController()))
	{
		 if (ABountyHUD* BountyHUD = Cast<ABountyHUD>(BountyPlayerController->GetHUD()))
		 {
			 BountyHUD->InitOverlay(BountyPlayerController, BountyPlayerState, AbilitySystemComponent, AttributeSet);
		 }
	}

	InitializeDefaultAttributes();
}
