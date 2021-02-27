// Fill out your copyright notice in the Description page of Project Settings.


#include "MClipHolder.h"


// Sets default values for this component's properties
UMClipHolder::UMClipHolder()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxClipCount = 0;
	ClipCount = 0;
	ReserveAmmoAttribute = nullptr;

	// ...
}


int32 UMClipHolder::GetClipCount()
{
	return ClipCount;
}

int32 UMClipHolder::GetMaxClipCount()
{
	return MaxClipCount;
}

void UMClipHolder::SetClipCount(int32 Count)
{
	ClipCount = Count;
}

void UMClipHolder::SetMaxClipCount(int32 Count)
{
	MaxClipCount = Count;
}

