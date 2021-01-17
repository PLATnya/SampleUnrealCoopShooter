


#include "MCharacterBase.h"
#include "Templates/UnrealTemplate.h"
AMCharacterBase::AMCharacterBase()
{
 
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UMAttributeSetCharacter>(TEXT("AttributeSet"));

	
	
	MainHandler.Hand = EHand::LEFT;
	AltHandler.Hand = EHand::RIGHT;
}

void AMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	AddCharacterAbilities();
	
	
 }


void AMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
bool AMCharacterBase::IsAlive() const
{
	return GetHealth() > 0.0f;
}

UAbilitySystemComponent* AMCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMCharacterBase::AddCharacterAbilities()
{
	// Grant abilities, but only on the server	
	if (GetLocalRole() != ROLE_Authority || !IsValid(AbilitySystemComponent))
	{
		return;
	}

	int index = 0;
	for (TSubclassOf<UGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
            FGameplayAbilitySpec(StartupAbility, 1, index, this));
		index++;
	}
}

float AMCharacterBase::GetHealth() const
{
	if (IsValid(AttributeSet))
	{
		return AttributeSet->GetHealth();
	}

	return 0.0f;
}
float AMCharacterBase::GetMaxHealth() const
{
	if (IsValid(AttributeSet))
	{
		
		return AttributeSet->GetMaxHealth();
	}
	
	return 0.0f;
}
void AMCharacterBase::SetHealth(float Health)
{
	if (IsValid(AttributeSet))
	{
		AttributeSet->SetHealth(Health);
	}else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,TEXT("not valid"));
	}
	
}


void AMCharacterBase::SwapHandlers()
{
	Swap(MainHandler,AltHandler);

}



float AMCharacterBase::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	SetHealth(FMath::Clamp(GetHealth() - ActualDamage, 0.0f,GetMaxHealth()));
	
	//UE_LOG(LogTemp,Display,TEXT("%s take %f damage from %s"),*GetNameSafe(this), ActualDamage, *GetNameSafe(DamageCauser) );
	return ActualDamage;
}

