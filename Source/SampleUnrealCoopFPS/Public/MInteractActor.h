// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "MInteractActor.generated.h"





UCLASS()
class SAMPLEUNREALCOOPFPS_API AMInteractActor : public AActor
{
	GENERATED_BODY()
	int32 UsersCount;
	UPROPERTY(EditDefaultsOnly)
	int32 UsersLimit;
	UPROPERTY(EditDefaultsOnly)
	bool bTwoHanded;

	bool bActive;
public:
	AMInteractActor();
	
	UFUNCTION(BlueprintCallable, Category="Interact")
	FORCEINLINE int32 GetUsersCount() const {return UsersCount;}
	UFUNCTION(BlueprintCallable, Category="Interact")
	FORCEINLINE int32 GetUsersLimit() const {return UsersLimit;}
	UFUNCTION(BlueprintCallable, Category="Interact")
    FORCEINLINE bool IsTwoHanded() const {return bTwoHanded;}
	UFUNCTION(BlueprintCallable, Category="Interact")
	void AddUser();
	UFUNCTION(BlueprintCallable, Category="Interact")
	bool TryDropFromHands();
	UFUNCTION(BlueprintCallable, Category="Interact")
	bool TryTake();
	UFUNCTION( Category="Interact")
	virtual bool TryDrop();
	UFUNCTION(BlueprintCallable,Category="Actor")
	void SetActive(bool Active) ;
	UFUNCTION(BlueprintCallable, Category="Actor")
	FORCEINLINE bool IsActive() const {return bActive;}
};
