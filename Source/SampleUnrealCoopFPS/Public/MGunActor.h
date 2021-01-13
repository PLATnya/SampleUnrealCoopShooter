// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.h"
#include "MGunActor.generated.h"

UCLASS()
class SAMPLEUNREALCOOPFPS_API AMGunActor : public AMInteractActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMGunActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
