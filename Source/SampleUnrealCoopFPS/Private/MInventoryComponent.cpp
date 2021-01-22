
#include "SampleUnrealCoopFPS/Public/MInventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "MCharacterBase.h"

void UMInventoryComponent::BeginPlay()
{
	APlayerController* WidgetOwner = Cast<APlayerController>(Cast<AMCharacterBase>(GetOwner())->GetController());
	ScreenAmmoWidget = CreateWidget<UUserWidget>(WidgetOwner,AmmoWidget);
	ScreenAmmoWidget->AddToPlayerScreen();

	
}

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
	Owner->MainHandler.HandTag;
	NewGun->AddAbilities(Guns.Num()+1,Owner->MainHandler.HandTag);
	
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
