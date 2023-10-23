// Copyright Dmytro Donets


#include "..\..\Public\Character\BountyCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/BountyPlayerState.h"

ABountyCharacter::ABountyCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = RotationRate;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;	
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;
}

void ABountyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Server
	InitAbilityActorInfo();
}

void ABountyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Client
	InitAbilityActorInfo();
}

void ABountyCharacter::InitAbilityActorInfo()
{
	ABountyPlayerState* BountyPlayerState = GetPlayerState<ABountyPlayerState>();
	check(BountyPlayerState);
	BountyPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(BountyPlayerState, this);
	AbilitySystemComponent = BountyPlayerState->GetAbilitySystemComponent();
	AttributeSet = BountyPlayerState->GetAttributeSet();
}
