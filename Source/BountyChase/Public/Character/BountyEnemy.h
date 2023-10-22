// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Character/BountyCharacterBase.h"
#include "Interaction/HighlightInterface.h"
#include "BountyEnemy.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyEnemy : public ABountyCharacterBase, public IHighlightInterface
{
	GENERATED_BODY()
public:
	ABountyEnemy();
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
