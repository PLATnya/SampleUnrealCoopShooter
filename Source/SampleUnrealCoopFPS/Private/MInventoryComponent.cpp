
#include "SampleUnrealCoopFPS/Public/MInventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "MCharacterBase.h"
#include "MPlayerCharacter.h"

void UMInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	APlayerController* WidgetOwner = Cast<APlayerController>(Cast<AMCharacterBase>(GetOwner())->GetController());
	ScreenAmmoWidget = CreateWidget<UUserWidget>(WidgetOwner,AmmoWidget);
	ScreenAmmoWidget->AddToPlayerScreen();
}

UMInventoryComponent::UMInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	GunsLimit = 5;
	AmmoWidget = nullptr;
}

 UMSpringArmComponent* UMInventoryComponent::AttachToArm(int32 Hand, AMGunActor* GunActor)
{
	AMPlayerCharacter* OwnerPlayer= Cast<AMPlayerCharacter>(GetOwner());
	UMSpringArmComponent* Arm = Hand==0?OwnerPlayer->LeftArm:OwnerPlayer->RightArm;
	GunActor->AttachToComponent(Arm, FAttachmentTransformRules::KeepRelativeTransform);
	return Arm;
}


bool UMInventoryComponent::TryAddGun(AMGunActor* NewGun)
{
	if(Guns.Num()>=GunsLimit||!NewGun->TryTake()) return false;
	AMPlayerCharacter* Owner = Cast<AMPlayerCharacter>(GetOwner());
	Guns.Add(NewGun);
	
	NewGun->SetAbilitySystemComponent(Owner->GetAbilitySystemComponent());
	NewGun->AddAbilities(Guns.Num()+1);

	NewGun->AttachToComponent(Owner->MainCamera,FAttachmentTransformRules::KeepRelativeTransform);
	NewGun->Hide();
	
	return true;
}



bool UMInventoryComponent::TryDropGun()
{
	AMCharacterBase* Owner = Cast<AMCharacterBase>(GetOwner());
	if(Owner->GetMainHandler().InteractHandler)
	{
		AMGunActor* Gun = Cast<AMGunActor>(Owner->GetMainHandler().InteractHandler);
		if(Gun)
		{
			if(Gun->TryDrop())
			{
				Guns.Remove(Gun);
				const FVector Offset = Owner->GetTransform().TransformPosition(FVector(100,0,-50));
				
				Gun->SetActorLocation(Offset);
				Owner->GetMainHandler().InteractHandler = nullptr;
				return true;
			}
		}
	}
	return false;
}
