

#include "SampleUnrealCoopFPS/Public/MGunActor.h"

#include "CollisionDebugDrawingPublic.h"
#include "DrawDebugHelpers.h"

AMGunActor::AMGunActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GunState = NewObject<UMLeftGunState>();
	WeaponTagsMap.Add("WeaponTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("WeaponReloadTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("WeaponShootTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("AmmoType", FGameplayTag::EmptyTag);
 }

void AMGunActor::Shoot()
{
	GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::SHOOT]);
}

void AMGunActor::Reload()
{
	GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::RELOAD]);
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
			
			//AttachToActor(Parent, FAttachmentTransformRules::KeepRelativeTransform);
			USceneComponent* CamManagerComponent = Cast<APlayerController>(ParentCharacter->GetController())->PlayerCameraManager->GetTransformComponent();
			AttachToComponent(CamManagerComponent,FAttachmentTransformRules::KeepRelativeTransform);
			//SetActorRotation(FRotator(0,ParentCharacter->GetActorRotation().Yaw,0));
			SetActorRelativeRotation(FRotator::ZeroRotator);
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
			DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);	
			return true;
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
	
	for (auto& Ability : Abilities)
	{
		const FGameplayAbilitySpec SpecHandle = FGameplayAbilitySpec(Ability.Value, 2, Index, this);
		
		if(SpecHandle.Ability->AbilityTags.HasTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"))||
			SpecHandle.Ability->AbilityTags.HasTag(WeaponTagsMap["WeaponTag"]))
		{
			AbilitySpecHandles.Add(Ability.Key,GetAbilitySystemComponent()->GiveAbility(SpecHandle));
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
	for (auto& SpecHandle : AbilitySpecHandles)
	{
		GetAbilitySystemComponent()->ClearAbility(SpecHandle.Value);
	}
}

