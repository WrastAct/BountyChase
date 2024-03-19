// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BountyAIController.generated.h"

class UBlackboardComponent;
class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API ABountyAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABountyAIController();
protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
