

#include "SampleUnrealCoopFPS/Public/MGunActor.h"
#include "AbilitySystemComponent.h"
#include "MCharacterBase.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "GameFramework/SpringArmComponent.h"


void AMGunActor::Hide()
{
	SetActive(false);
}

void AMGunActor::Show()
{
	SetActive(true);
}

void AMGunActor::Config()
{
	SetActorRelativeLocation(FVector::ZeroVector);
}

AMGunActor::AMGunActor()
{
	PrimaryActorTick.bCanEverTick = true;
	ClipHolder = CreateDefaultSubobject<UMClipHolder>("ClipHolder");
	
	RootComponent = CreateDefaultSubobject<USceneComponent>("GunRoot");
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunSkeletMesh");
	SkeletalMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ShakeSource = CreateDefaultSubobject<UCameraShakeSourceComponent>("Shake");
	ShakeSource->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	WeaponTagsMap.Add("WeaponTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("HandTag",FGameplayTag::EmptyTag);
}


void AMGunActor::Shoot()
{
	GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::SHOOT]);
}


void AMGunActor::Reload()
{
	GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::RELOAD]);
}


UAbilitySystemComponent* AMGunActor::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMGunActor::SetAbilitySystemComponent(UAbilitySystemComponent* Asc)
{
	AbilitySystemComponent = Asc;
}

void AMGunActor::AddAbilities(int32 InLevel)
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
	for (auto& Ability : Abilities)
	{
		const FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability.Value.GetDefaultObject(), InLevel, Index, this);
		AbilitySpecHandles.Add(Ability.Key,GetAbilitySystemComponent()->GiveAbility(Spec));
		Index++;
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



