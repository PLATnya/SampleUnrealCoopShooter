

#include "SampleUnrealCoopFPS/Public/MGunActor.h"
#include "AbilitySystemComponent.h"
#include "MCharacterBase.h"
#include "Camera/CameraShakeSourceComponent.h"

void AMGunActor::OnReloadEnd(const FAbilityEndedData& Data)
{
	if(Data.AbilitySpecHandle == AbilitySpecHandles[EGunActions::RELOAD])
	{
		bCanStartShoot = true;
	}
}


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
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("GunSkeletMesh");
	SkeletalMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ShakeSource = CreateDefaultSubobject<UCameraShakeSourceComponent>("Shake");
	ShakeSource->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	WeaponTagsMap.Add("WeaponTag", FGameplayTag::RequestGameplayTag("Weapon"));
	WeaponTagsMap.Add("HandTag",FGameplayTag::EmptyTag);

	bCanStartShoot = true;
}

UGameplayEffect* AMGunActor::MakeAmmoEffect(float Magnitude)
{
	// Create a dynamic instant Gameplay Effect to give the bounties
	UGameplayEffect* GEBounty = NewObject<UGameplayEffect>(GetTransientPackage(), FName(TEXT("Bounty")));
	GEBounty->DurationPolicy = EGameplayEffectDurationType::Instant;

	GEBounty->Modifiers.SetNum(1);

	FGameplayModifierInfo& InfoAmmo = GEBounty->Modifiers[0];
	InfoAmmo.ModifierMagnitude = FScalableFloat(Magnitude);
	InfoAmmo.ModifierOp = EGameplayModOp::Additive;
	InfoAmmo.Attribute = ReserveAmmoAttribute;
	
	return GEBounty;
	
}

void AMGunActor::Shoot_Implementation(FName SocketName)
{
	
	if(GetClipCount()>0)
	{
		if(ShakeSource->CameraShake)ShakeSource->Start();
		FVector Location = FVector(0,0,0);
		FRotator Rotation = FRotator(0,0,0);
		if(SkeletalMesh->MeshObject)
		{
			Location = SkeletalMesh->GetSocketLocation(SocketName);
			Rotation = SkeletalMesh->GetSocketRotation(SocketName);
			
		}
		GetWorld()->SpawnActor<AActor>(Projectile,Location,Rotation);
		
		if(SkeletalMesh->GetAnimInstance())
			SkeletalMesh->GetAnimInstance()->Montage_Play(ActionMontages[EGunActions::SHOOT]);
		SetClipCount(GetClipCount()-1);
	}
}

void AMGunActor::Reload()
{
	if(bCanStartShoot)
	{
		if(GetClipCount()<GetMaxClipCount()){
			bool bActivatedReload = GetAbilitySystemComponent()->TryActivateAbility(AbilitySpecHandles[EGunActions::RELOAD]);
			if(bActivatedReload) bCanStartShoot = false;
		}
	}
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

void AMGunActor::AddAbilities(int32 InLevel, FGameplayTag HandTag)
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
		//TODO:какого хрена HasAny тут не фурычит?
		const FGameplayAbilitySpec Spec = FGameplayAbilitySpec(Ability.Value.GetDefaultObject(), InLevel, Index, this);
		
		UE_LOG(LogTemp,Warning,TEXT("%s"),*GetNameSafe(Spec.Ability));
		if(Spec.Ability->AbilityTags.HasTag(FGameplayTag::RequestGameplayTag("Ability.Weapon.Gun"))|| Spec.Ability->AbilityTags.HasTag(WeaponTagsMap["WeaponTag"]))
		{
			AbilitySpecHandles.Add(Ability.Key,GetAbilitySystemComponent()->GiveAbility(Spec));
			Index++;
		}
		

	}
	GetAbilitySystemComponent()->OnAbilityEnded.AddUObject(this, &AMGunActor::OnReloadEnd);
	
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

