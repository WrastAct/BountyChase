// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/BountyGameplayAbility.h"
#include "BountySpawnActors.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountySpawnActors : public UBountyGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category="Spawning")
	TSubclassOf<AActor> GetRandomActorClass();

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	int32 NumActors = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TArray<TSubclassOf<AActor>> ActorClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float MaxSpawnDistance = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	float SpawnSpread = 90.f;
};
