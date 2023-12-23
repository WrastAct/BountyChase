// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BountyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class BOUNTYCHASE_API ABountyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABountyProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

};
