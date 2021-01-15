// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MGunActor.h"


// Sets default values
AMGunActor::AMGunActor()
{
	
	PrimaryActorTick.bCanEverTick = true;
	GunState = NewObject<UMLeftGunState>();	
}

// Called when the game starts or when spawned
void AMGunActor::BeginPlay()
{
	Super::BeginPlay();
	GunState->SetGun(this);
}





void AMGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

