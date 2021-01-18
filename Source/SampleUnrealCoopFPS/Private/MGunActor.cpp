﻿

#include "SampleUnrealCoopFPS/Public/MGunActor.h"

AMGunActor::AMGunActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GunState = NewObject<UMLeftGunState>();
	WeaponTagsMap.Add("WeaponTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("WeaponReloadTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("WeaponShootTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("AmmoType", FGameplayTag::EmptyTag);
 }


int32 AMGunActor::GetClipCount()
{
	return ClipCount;
}

int32 AMGunActor::GetMaxClipCount()
{
	return MaxClipCount;
}

void AMGunActor::SetClipCount(int32 Count)
{
	ClipCount = Count;
}

void AMGunActor::SetMaxClipCount(int32 Count)
{
	MaxClipCount = Count;
}

bool AMGunActor::TryGet(AActor* Parent)
{
	if(Super::TryGet(Parent))
	{
		AMCharacterBase* ParentCharacter = Cast<AMCharacterBase>(Parent);
		if(ParentCharacter)
		{
			AttachToComponent(Cast<APlayerController>(ParentCharacter->GetController())->PlayerCameraManager->GetTransformComponent(),FAttachmentTransformRules::KeepRelativeTransform);
		}
		return true;
	}
	return false;
}

bool AMGunActor::TryDrop()
{
	if(Super::TryDrop())
	{
		
		AActor* Parent = GetAttachParentActor();
		if(Parent)
		{
			FHitResult OutHit;
			FVector Offset = Parent->GetTransform().TransformPosition(FVector(100,0,-100));
			FCollisionQueryParams Params;
			Params.AddIgnoredActor(Parent);
			Params.AddIgnoredActor(this);
			
			bool bRaycast = ActorLineTraceSingle(OutHit, Parent->GetActorLocation(),Parent->GetActorLocation()+Offset,ECollisionChannel::ECC_Visibility,Params);
			if(bRaycast&&!OutHit.bBlockingHit)
			{
				DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
				SetActorLocation(Parent->GetActorLocation()+Offset);
				SetActorRotation(FRotator::ZeroRotator );
				return true;
			}
			
		}
		
	}
	return false;
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
	WeaponTagsContainer.AddTag(WeaponTagsMap["WeaponTag"]);
	
	WeaponTagsContainer.AddTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"));
	for (TSubclassOf<UGameplayAbility>& Ability : Abilities)
	{
		const FGameplayAbilitySpec SpecHandle = FGameplayAbilitySpec(Ability, 2, Index, this);
		
		if(SpecHandle.Ability->AbilityTags.HasTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"))||
			SpecHandle.Ability->AbilityTags.HasTag(WeaponTagsMap["WeaponTag"]))
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

