#pragma once

#include "GameplayEffectTypes.h"
#include "BountyAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FBountyGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:

	bool IsDodgedHit () const { return bIsDodgedHit; }

	void SetIsDodgedHit(bool bInIsDodgedHit) { bIsDodgedHit = bInIsDodgedHit; }

	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return StaticStruct();
	}
	
	/** Creates a copy of this context, used to duplicate for later modifications */
	virtual FBountyGameplayEffectContext* Duplicate() const
	{
		FBountyGameplayEffectContext* NewContext = new FBountyGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);

protected:

	UPROPERTY()
	bool bIsDodgedHit = false;

};

template<>
struct TStructOpsTypeTraits<FBountyGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FBountyGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};