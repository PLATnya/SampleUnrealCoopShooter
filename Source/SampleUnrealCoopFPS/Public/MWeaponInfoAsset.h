// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MGunActor.h"
#include "Engine/DataAsset.h"
#include "MWeaponInfoAsset.generated.h"


UCLASS()
class SAMPLEUNREALCOOPFPS_API UMWeaponInfoAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Info")
	TSubclassOf<AMGunActor> GunClass;
	FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Guns", GetFName());
	}	
};
