

#include "SampleUnrealCoopFPS/Public/MGunActor.h"
#include "AbilitySystemComponent.h"
#include "MCharacterBase.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "GameFramework/SpringArmComponent.h"

void AMGunActor::BeginPlay()
{
	Super::BeginPlay();
	
	
}

AMGunActor::AMGunActor()
{
	PrimaryActorTick.bCanEverTick = true;
	GunState = NewObject<UMLeftGunState>();
	
	//SkeletalMesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	RootComponent = CreateDefaultSubobject<USceneComponent>("GunRoot");
	ArmComponent = CreateDefaultSubobject<USpringArmComponent>("Arm");
	ArmComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunSkeletMesh");
	SkeletalMesh->AttachToComponent(ArmComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ShakeSource = CreateDefaultSubobject<UCameraShakeSourceComponent>("Shake");
	ShakeSource->AttachToComponent(ArmComponent,FAttachmentTransformRules::KeepRelativeTransform);
	WeaponTagsMap.Add("WeaponTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("HandTag",FGameplayTag::EmptyTag);

	bCanStartShoot = true;
}


void AMGunActor::AbilityShoot()
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
			USceneComponent* CamManagerComponent = Cast<APlayerController>(ParentCharacter->GetController())->PlayerCameraManager->GetTransformComponent();
			AttachToComponent(CamManagerComponent,FAttachmentTransformRules::KeepRelativeTransform);
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
		UGameplayAbility* f = NewObject<UMGameplayAbility>();
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

