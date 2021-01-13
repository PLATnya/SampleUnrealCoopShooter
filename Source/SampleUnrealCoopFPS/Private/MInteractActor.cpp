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

bool AMInteractActor::TryGet()
{
	if(UsersCount< UsersLimit)
	{
		UsersCount++;
		return true;
	}
	return false;
}

void AMInteractActor::SetActive(bool Active)
{
	SetActorHiddenInGame(!Active);
	SetActorEnableCollision(Active);
	SetActorTickEnabled(Active);
}

// Called every frame
void AMInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}





