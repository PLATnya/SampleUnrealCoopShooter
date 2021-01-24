
#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "MGameplayAbility.generated.h"


UCLASS()
class SAMPLEUNREALCOOPFPS_API UMGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	public:
	UFUNCTION(BlueprintCallable)
	void AddBlockedTags(FGameplayTagContainer Container);
	UFUNCTION(BlueprintCallable)
	void TryRemoveBlockedTags(FGameplayTagContainer Container);
	
};
