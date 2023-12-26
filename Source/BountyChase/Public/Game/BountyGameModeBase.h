// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BountyGameModeBase.generated.h"

class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Character Class Defaults")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;
};
