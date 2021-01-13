


#include "MCharacterBase.h"

AMCharacterBase::AMCharacterBase()
{
 
	PrimaryActorTick.bCanEverTick = true;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	AttributeSet = CreateDefaultSubobject<UMAttributeSetCharacter>(TEXT("AttributeSet"));

	
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
	}
}

bool AMCharacterBase::GetInHand(AMInteractActor* InteractActor)
{
	if(InteractActor->SetUser(this))
	{
		const bool LeftHandValid = IsValid(LeftHandHandler);
		const bool RightHandValid = IsValid(RightHandHandler);
		if(InteractActor->bInLeftHand&&InteractActor->bInRightHand)
		{
			if(!LeftHandValid&&!RightHandValid)
			{
			
				LeftHandHandler = InteractActor;
				RightHandHandler = InteractActor;
				return true;
			}
		}else
		{
			if(InteractActor->bInRightHand)
			{
			
				RightHandHandler = InteractActor;
				return true;
			}
			if(InteractActor->bInLeftHand)
			{
				LeftHandHandler = InteractActor;
				return true;
			}
		}
	}
	return false;
}





