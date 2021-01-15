// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleUnrealCoopFPS/Public/MInventoryComponent.h"


// Sets default values for this component's properties
UMInventoryComponent::UMInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	GunsLimit = 5;
	// ...
}


// Called when the game starts
void UMInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool UMInventoryComponent::TryAddGun(AMGunActor* NewGun, AActor* Owner)
{
	if(!NewGun->TryGet(Owner)) return false; 
	if(Guns.Num()>=GunsLimit) return false;

	Guns.Add(NewGun);
	if(!NewGun->GunState)
	{
		UMLeftGunState* NewState = NewObject<UMLeftGunState>();
		NewGun->GunState = NewState;
		NewGun->GunState->SetGun(NewGun);
		NewState->Config();
	}
	NewGun->GunState->Hide();
	return true;
}

// Called every frame
void UMInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

