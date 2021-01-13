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

// Called every frame
void AMInteractActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AMInteractActor::SetUser(AMCharacterBase* User)
{
	if(Users.Num()<UsersLimit)
	{
		Users.Add(User);
		return true;
	}
	return false;
}

bool AMInteractActor::BreakUser(AMCharacterBase* User)
{
	const int BuffSize = Users.Num();
	Users.Remove(User);
	if(BuffSize>Users.Num())
	{
		if(bInLeftHand) User->LeftHandHandler = NULL;
		if(bInRightHand) User->RightHandHandler = NULL;
		return true;
	}
	return false;
}

