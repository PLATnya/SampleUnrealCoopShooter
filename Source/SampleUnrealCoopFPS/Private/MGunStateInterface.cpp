// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MGunStateInterface.h"
#include "Components/SceneComponent.h"






void UMGunStateInterface::SetGun(AMGunActor* NewGun)
{
	Gun = NewGun;
}

void UMGunStateInterface::Config(const FVector Offset, const FVector OutOffset)
{
	//if(Gun->GetParentActor()!=Character) Gun->AttachToActor(Character,FAttachmentTransformRules::KeepWorldTransform);
	
	 Gun->SetActorRelativeLocation(Offset);
}



void UMGunStateInterface::Hide()
{
	Gun->SetActive(false);
}

void UMGunStateInterface::Show()
{
	Gun->SetActive(true);
	
}



void UMLeftGunState::Config(const FVector Offset, const FVector OutOffset)
{
	Super::Config( Offset,OutOffset);
}



void UMRightGunState::Config(const FVector Offset, const FVector OutOffset)
{
	Super::Config( Offset,OutOffset);
}



void UMCenterGunState::Config(const FVector Offset, const FVector OutOffset)
{
	Super::Config( Offset,OutOffset);
}

