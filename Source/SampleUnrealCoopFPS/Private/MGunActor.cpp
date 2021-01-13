// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MGunActor.h"


// Sets default values
AMGunActor::AMGunActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMGunActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMGunActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

