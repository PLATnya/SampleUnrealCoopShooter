// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MGunActor.h"


// Sets default values
AMGunActor::AMGunActor()
{
	
	PrimaryActorTick.bCanEverTick = true;
	GunState = NewObject<UMLeftGunState>();	
}

// Called when the game starts or when spawned
void AMGunActor::BeginPlay()
{
	Super::BeginPlay();
	//GunState->SetGun(this);
}





void AMGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* AMGunActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMGunActor::SetAbilitySystemComponent(UAbilitySystemComponent* Asc)
{
	AbilitySystemComponent = Asc;
}

void AMGunActor::AddAbilities()
{
	if (!GetAbilitySystemComponent())
	{
		return;
	}
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	int32 Index = 0;
	
	
	
	
	FGameplayTagContainer WeaponTagsContainer;
	WeaponTagsContainer.AddTag(WeaponTag);
	
	WeaponTagsContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"));
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		const FGameplayAbilitySpec SpecHandle = FGameplayAbilitySpec(Ability, 2, Index, this);
		
		if(SpecHandle.Ability->AbilityTags.HasTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"))||
			SpecHandle.Ability->AbilityTags.HasTag(WeaponTag))
		{
			AbilitySpecHandles.Add(GetAbilitySystemComponent()->GiveAbility(SpecHandle));
			Index++;
		}
	}
	
}
void AMGunActor::RemoveAbilities()
{
	if (!GetAbilitySystemComponent())
	{
		return;
	}

	
	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	for (FGameplayAbilitySpecHandle& SpecHandle : AbilitySpecHandles)
	{
		GetAbilitySystemComponent()->ClearAbility(SpecHandle);
	}
}

