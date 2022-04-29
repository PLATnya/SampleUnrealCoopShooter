// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameplayAbility.h"

void UMGameplayAbility::AddBlockedTags(FGameplayTagContainer Container)
{
	
	BlockAbilitiesWithTag.AppendTags(Container);
}
void UMGameplayAbility::TryRemoveBlockedTags(FGameplayTagContainer Container)
{
	BlockAbilitiesWithTag.RemoveTags(Container);
}
