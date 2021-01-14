// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MGunActor.h"
#include "Components/ActorComponent.h"
#include "MInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLEUNREALCOOPFPS_API UMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintReadOnly)
	TSet<AMGunActor*> Guns;

	UPROPERTY(BlueprintReadWrite)
	int32 GunsLimit;

	UFUNCTION(BlueprintCallable)
	bool TryAdd(AMGunActor* NewGun);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
