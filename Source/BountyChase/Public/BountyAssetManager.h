// Copyright Dmytro Donets

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "BountyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class BOUNTYCHASE_API UBountyAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:

	static UBountyAssetManager& Get();

protected:

	virtual void StartInitialLoading() override;
};
