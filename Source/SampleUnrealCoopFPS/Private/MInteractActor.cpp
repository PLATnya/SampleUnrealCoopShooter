
#include "MInteractActor.h"

AMInteractActor::AMInteractActor()
{
	
	PrimaryActorTick.bCanEverTick = true;
}
bool AMInteractActor::TryGet(AActor* Parent )
{
	if(UsersCount< UsersLimit)
	{
		UsersCount++;
		return true;
	}
	return false;
}

bool AMInteractActor::TryDrop()
{
	UsersCount--;
	return true;	
}

void AMInteractActor::SetActive(bool Active)
{
	SetActorEnableCollision(Active);
	SetActorHiddenInGame(!Active);
	SetActorTickEnabled(Active);
}




