
#include "SampleUnrealCoopFPS/Public/MInventoryComponent.h"
UMInventoryComponent::UMInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	GunsLimit = 5;

}


bool UMInventoryComponent::TryAddGun(AMGunActor* NewGun)
{
	AMCharacterBase* Owner = Cast<AMCharacterBase>(GetOwner());
	if(!NewGun->TryGet(Owner)) return false; 
	if(Guns.Num()>=GunsLimit) return false;
	
	Guns.Add(NewGun);	
	NewGun->SetAbilitySystemComponent(Owner->GetAbilitySystemComponent());
	NewGun->AddAbilities();
	
	if(!NewGun->GunState)
	{
		UMCenterGunState* NewState = NewObject<UMCenterGunState>();
		NewGun->GunState = NewState;
		NewGun->GunState->SetGun(NewGun);
		NewState->Config();
	}
	NewGun->GunState->Hide();
	return true;
}

bool UMInventoryComponent::TryDropGun()
{
	AMCharacterBase* Owner = Cast<AMCharacterBase>(GetOwner());
	if(Owner->MainHandler.InteractHandler)
	{
		AMGunActor* Gun = Cast<AMGunActor>(Owner->MainHandler.InteractHandler);
		if(Gun)
		{
			if(Gun->TryDrop())
			{
				Guns.Remove(Gun);
				const FVector Offset = Owner->GetTransform().TransformPosition(FVector(100,0,-50));
				
				Gun->SetActorLocation(Offset);
				Owner->MainHandler.InteractHandler = nullptr;
				return true;
			}
		}
	}
	return false;
}
