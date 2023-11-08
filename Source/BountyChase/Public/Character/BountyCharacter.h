// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Character/BountyCharacterBase.h"
#include "BountyCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyCharacter : public ABountyCharacterBase
{
	GENERATED_BODY()
public:
	ABountyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

private:
	virtual void InitAbilityActorInfo() override;
	
private:
	UPROPERTY(EditAnywhere, Category="Movement")
	FRotator RotationRate = FRotator(0.f, 500.f, 0.f);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
};
