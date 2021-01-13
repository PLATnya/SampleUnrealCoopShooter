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
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly)
	TArray<AMCharacterBase*> Users;
	
	UPROPERTY(BlueprintReadWrite)
	int32 UsersLimit;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual bool SetUser(AMCharacterBase* User);
	virtual bool BreakUser(AMCharacterBase* User);

	UPROPERTY(BlueprintReadOnly)
	bool bInRightHand;
	UPROPERTY(BlueprintReadOnly)
	bool bInLeftHand;
	
};
