// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MCharacterBase.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.generated.h"





UCLASS()
class SAMPLEUNREALCOOPFPS_API AMInteractActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMInteractActor();

protected:
	
	
	int32 UsersCount;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(BlueprintReadWrite)
	int32 UsersLimit;

	UFUNCTION(BlueprintCallable, Category="Interact")
	virtual bool TryGet();

	UFUNCTION(BlueprintCallable,Category="Interact")
	//void SetActive(bool Active);
	
	virtual void Tick(float DeltaTime) override;

	
	
	UPROPERTY(BlueprintReadWrite)
	bool bInRightHand;
	UPROPERTY(BlueprintReadWrite)
	bool bInLeftHand;
	
};
