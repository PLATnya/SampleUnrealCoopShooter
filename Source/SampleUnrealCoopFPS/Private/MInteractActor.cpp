
#include "MInteractActor.h"

AMInteractActor::AMInteractActor()
{	
	PrimaryActorTick.bCanEverTick = true;
	bActive = true;
}

void AMInteractActor::AddUser()
{
	UsersCount++;
}

bool AMInteractActor::TryDropFromHands()
{
	if(TryDrop())
	{
		AActor* Parent = GetAttachParentActor();		
		if(Parent)
		{
			DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);	
			return true;
		}
	}
	return false;
}

bool AMInteractActor::TryTake()
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
	if(UsersCount>0)
	UsersCount--;
	else return false;
	return true;	
}

void AMInteractActor::SetActive(bool Active)
{
	bActive = Active;
	SetActorEnableCollision(Active);
	SetActorHiddenInGame(!Active);
	SetActorTickEnabled(Active);
}




