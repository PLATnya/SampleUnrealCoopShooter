// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MInteractActor.generated.h"





UCLASS()
class SAMPLEUNREALCOOPFPS_API AMInteractActor : public AActor
{
	GENERATED_BODY()
protected:
	int32 UsersCount;
	UPROPERTY(BlueprintReadWrite)
	int32 UsersLimit;
public:
	AMInteractActor();

	UPROPERTY(BlueprintReadWrite)
	bool bTwoHanded;
	
	
	UFUNCTION(BlueprintCallable, Category="Interact")
	virtual bool TryGet(AActor* Parent = nullptr);
	UFUNCTION(BlueprintCallable, Category="Interact")
	virtual bool TryDrop();
	UFUNCTION(BlueprintCallable,Category="Interact")
	virtual void SetActive(bool Active) ;	
};
