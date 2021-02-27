// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeSet.h"
#include "MClipHolder.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLEUNREALCOOPFPS_API UMClipHolder : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMClipHolder();

protected:
	UPROPERTY(EditAnywhere,Category="Clip")
	int32 MaxClipCount;
	UPROPERTY(EditAnywhere,Category="Clip")
	int32 ClipCount;
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS")
	FGameplayAttribute ReserveAmmoAttribute;
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
    int32 GetClipCount ();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
    int32 GetMaxClipCount();
	UFUNCTION(BlueprintCallable, Category="Weapon")
    void SetClipCount(int32 Count);
	UFUNCTION(BlueprintCallable, Category="Weapon")
    void SetMaxClipCount(int32 Count);
};
