// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.h"
#include "MGunStateInterface.h"

#include "MGunActor.generated.h"












UCLASS()
class SAMPLEUNREALCOOPFPS_API AMGunActor : public AMInteractActor
{
	GENERATED_BODY()

public:
	
	AMGunActor();

protected:
	virtual void BeginPlay() override;

public:
	class UMGunStateInterface *GunState;
	
	
	virtual void Tick(float DeltaTime) override;
};
