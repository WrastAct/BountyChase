// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "BountyPlayerController.generated.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UBountyInputConfig;
class UBountyAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABountyPlayerController();
	virtual void PlayerTick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> BountyContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> DashAction;
	
	void CursorTrace();
	TObjectPtr<AActor> LastActor;
	TObjectPtr<AActor> ThisActor;
	FHitResult CursorHit;
	static void HighlightActor(AActor* InActor);
	static void UnHighlightActor(AActor* InActor);

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue); // Might want to remove
	void Dash(const FInputActionValue& InputActionValue);

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UBountyInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UBountyAbilitySystemComponent> BountyAbilitySystemComponent;

	UBountyAbilitySystemComponent* GetASC();
};
