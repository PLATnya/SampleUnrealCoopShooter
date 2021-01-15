// Fill out your copyright notice in the Description page of Project Settings.


#include "MInteractActor.h"


// Sets default values
AMInteractActor::AMInteractActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMInteractActor::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AMInteractActor::TryGet(AActor* Parent )
{
	if(UsersCount< UsersLimit)
	{
		UsersCount++;

		if(Parent) AttachTo(Parent);
		return true;
	}
	return false;
}
void AMInteractActor::AttachTo(AActor* Parent)
{
	AttachToActor(Parent, FAttachmentTransformRules::KeepRelativeTransform);
}
/*
void AMInteractActor::SetActive(bool Active)
{
	
	//this->SetActorHiddenInGame(!Active);
	try
	{
		SetActorEnableCollision(Active);
		const bool bInverse = !Active;
		SetActorHiddenInGame(bInverse);
		SetActorTickEnabled(Active);
	}catch (std::exception& ex)
	{
		
		UE_LOG(LogTemp,Warning,TEXT("%s"),ex.what());
	}
	
}*/

void AMInteractActor::SetActive(bool Active)
{
	SetActorEnableCollision(Active);
	
	
	SetActorHiddenInGame(!Active);
	SetActorTickEnabled(Active);
}

// Called every frame
void AMInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





