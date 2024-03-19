// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Character/BountyCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "BountyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyCharacter : public ABountyCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
public:
	ABountyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Player Interface */
	virtual int32 GetSpellPoints_Implementation() const override;
	virtual int32 GetSpellPointsReward_Implementation(int32 Level) const override;
	virtual void AddToSpellPoints_Implementation(int32 InSpellPoints) override;
	/* end Player Interface */

	virtual int32 GetPlayerLevel_Implementation() override;

private:
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Movement")
	FRotator RotationRate = FRotator(0.f, 500.f, 0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* TopDownCamera;
};
