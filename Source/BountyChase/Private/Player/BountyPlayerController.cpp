// Copyright Dmytro Donets


#include "Player/BountyPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "BountyGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/BountyAbilitySystemComponent.h"
#include "Input/BountyInputComponent.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/HighlightInterface.h"
#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

ABountyPlayerController::ABountyPlayerController()
{
	bReplicates = true;
}

void ABountyPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void ABountyPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter, bool bDodgedHit)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass && IsLocalController())
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent();
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount, bDodgedHit);
	}
}

void ABountyPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	// GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void ABountyPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
}

void ABountyPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
}

UBountyAbilitySystemComponent* ABountyPlayerController::GetASC()
{
	if (BountyAbilitySystemComponent == nullptr)
	{
		BountyAbilitySystemComponent = Cast<UBountyAbilitySystemComponent>(
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>())
		);
	}
	return BountyAbilitySystemComponent;
}

void ABountyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(BountyContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
		GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(BountyContext, 0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void ABountyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UBountyInputComponent* BountyInputComponent = CastChecked<UBountyInputComponent>(InputComponent);

	BountyInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABountyPlayerController::Move);
	// BountyInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABountyPlayerController::Look);
	BountyInputComponent->BindAction(DashAction, ETriggerEvent::Started, this, &ABountyPlayerController::Dash);

	BountyInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
	                                         &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ABountyPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;
	
	LastActor = ThisActor;
	if (IsValid(CursorHit.GetActor()) && CursorHit.GetActor()->Implements<UHighlightInterface>())
	{
		ThisActor = CursorHit.GetActor();
	}
	else
	{
		ThisActor = nullptr;
	}
	
	if (LastActor != ThisActor)
	{
		UnHighlightActor(LastActor);
		HighlightActor(ThisActor);
	}
}

void ABountyPlayerController::HighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_HighlightActor(InActor);
	}
}

void ABountyPlayerController::UnHighlightActor(AActor* InActor)
{
	if (IsValid(InActor) && InActor->Implements<UHighlightInterface>())
	{
		IHighlightInterface::Execute_UnHighlightActor(InActor);
	}
}

void ABountyPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.0, Rotation.Yaw, 0.0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ABountyPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
}

void ABountyPlayerController::Dash(const FInputActionValue& InputActionValue)
{
	const bool IsPressed = InputActionValue.Get<bool>();
	//todo: implement dash logic
}
