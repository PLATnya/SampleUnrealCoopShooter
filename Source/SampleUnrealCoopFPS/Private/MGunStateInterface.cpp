// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MGunStateInterface.h"
#include "Components/SceneComponent.h"



void UMGunStateInterface::SetGun(AMGunActor* Gun)
{
	this->Gun = Gun;
}

void UMGunStateInterface::Config(AMCharacterBase* Character, const FVector Offset, const FVector OutOffset)
{
	if(Gun->GetParentActor()!=Character) Gun->AttachToActor(Character,FAttachmentTransformRules::KeepWorldTransform);
	Gun->SetActorLocation(Character->GetActorTransform().TransformPosition(Offset));
}

void UMGunStateInterface::Hide()
{
	Gun->SetActive(false);
}

void UMGunStateInterface::Show()
{
	Gun->SetActive(true);
}



void UMLeftGunState::Config( AMCharacterBase* Character)
{
	Super::Config(Character, FVector(50,50,50),FVector(50,50,50));
}



void UMRightGunState::Config( AMCharacterBase* Character)
{
	Super::Config(Character, FVector(-50,50,50),FVector(-50,50,50));
}

void UMCenterGunState::Config(AMCharacterBase* Character)
{
	Super::Config(Character, FVector(0,50,50),FVector(0,50,50));
}

