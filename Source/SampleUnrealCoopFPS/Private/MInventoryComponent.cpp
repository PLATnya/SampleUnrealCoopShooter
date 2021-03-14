﻿
#include "SampleUnrealCoopFPS/Public/MInventoryComponent.h"

#include "Blueprint/UserWidget.h"
#include "MCharacterBase.h"
#include "MPlayerCharacter.h"
#include "Engine/DemoNetDriver.h"

void UMInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

UMInventoryComponent::UMInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	GunsLimit = 5;
	AmmoWidget = nullptr;
}

void UMInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UMInventoryComponent,Guns);
}

void UMInventoryComponent::AddInventoryWidgetOnScreen(APlayerController* Controller)
{
	if(!Controller)
	{
		UE_LOG(LogTemp,Warning,TEXT("IT IS NO FUCKING CONTROLLER"));
		return;
	}
	ScreenAmmoWidget = CreateWidget<UUserWidget>(Controller,AmmoWidget);
	ScreenAmmoWidget->AddToPlayerScreen();
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
	NewGun->SetOwner(Owner);
	NewGun->SetAbilitySystemComponent(Owner->GetAbilitySystemComponent());
	NewGun->AddAbilities(1);
//Guns.Num()+1
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
