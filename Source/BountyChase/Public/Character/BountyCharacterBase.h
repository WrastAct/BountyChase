// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BountyCharacterBase.generated.h"

UCLASS(Abstract)
class BOUNTYCHASE_API ABountyCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ABountyCharacterBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
};
