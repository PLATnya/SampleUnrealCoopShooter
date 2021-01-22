
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MGameplayAbility.generated.h"


UCLASS()
class SAMPLEUNREALCOOPFPS_API UMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	public:
	UFUNCTION()
	void AddBlockedTags(FGameplayTagContainer Container);
	UFUNCTION()
	void TryRemoveBlockedTags(FGameplayTagContainer Container);
	
};
