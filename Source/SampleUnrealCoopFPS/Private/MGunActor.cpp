

#include "SampleUnrealCoopFPS/Public/MGunActor.h"
#include "AbilitySystemComponent.h"
#include "MCharacterBase.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "Engine/DemoNetDriver.h"
#include "GameFramework/SpringArmComponent.h"
#include "SampleUnrealCoopFPS/SampleUnrealCoopFPS.h"


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
	RootComponent->SetRelativeLocation(FVector::ZeroVector);
	SetActorRelativeLocation(FVector::ZeroVector);
	RootComponent->SetRelativeRotation(FRotator::ZeroRotator);
	SetActorRelativeRotation(FRotator::ZeroRotator);
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
	WeaponTagsMap.Add("ShootTag",FGameplayTag::EmptyTag);


	SpecHandlesMapContainer = NewObject<UAbilitySpecHandlesMapContainer>();
}


void AMGunActor::Shoot()
{
	AMCharacterBase* OwnerCharacter = Cast<AMCharacterBase>(GetOwner());
	const bool SuccessActivation = OwnerCharacter->GetAbilitySystemComponent()->TryActivateAbility((*SpecHandlesMapContainer)[EGunActions::SHOOT]);
#ifdef UE_BUILD_DEBUG
	if(HasAuthority())
	{
		UE_LOG(MLOG, Log, TEXT("IT IS A SERVER SHOOT"));
	}
	else
		UE_LOG(MLOG, Log, TEXT("IT IS A CLIENT SHOOT"));
	if(!SuccessActivation) UE_LOG(MLOG,Warning,TEXT("NO SUCCES SHOOT ACTIVATIN"));
#endif

}


void AMGunActor::Reload()
{
	//GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::RELOAD]);
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
	if (!GetAbilitySystemComponent()||!HasAuthority())
	{
		return;
	}
	
	//int32 Index = 0;
	for (auto& Ability : Abilities)
	{
		const FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability.Value.GetDefaultObject(), InLevel, INDEX_NONE, this);
		
		SpecHandlesMapContainer->AbilitySpecHandles.Add(Ability.Key,GetAbilitySystemComponent()->GiveAbility(Spec));
		
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
	
	for (auto& SpecHandle : SpecHandlesMapContainer->AbilitySpecHandles)
	{
		GetAbilitySystemComponent()->ClearAbility(SpecHandle.Value);
	}
}



