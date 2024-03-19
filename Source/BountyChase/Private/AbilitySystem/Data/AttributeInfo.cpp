// Copyright Dmytro Donets


#include "AbilitySystem/Data/AttributeInfo.h"

#include "BountyChase/BountyLogChannels.h"

FBountyAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FBountyAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogBounty, Error, TEXT("Can't find info for AttributeTag [%s] on AttributeInfo [%s]."),
		       *AttributeTag.ToString(), *GetNameSafe(this));
	}

	return FBountyAttributeInfo();
}
