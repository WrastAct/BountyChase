// Copyright Dmytro Donets


#include "BountyAssetManager.h"
#include "BountyGameplayTags.h"

UBountyAssetManager& UBountyAssetManager::Get()
{
	check(GEngine);
	
	UBountyAssetManager* BountyAssetManager = Cast<UBountyAssetManager>(GEngine->AssetManager);
	return *BountyAssetManager;
}

void UBountyAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FBountyGameplayTags::InitializeNativeGameplayTags();
}
