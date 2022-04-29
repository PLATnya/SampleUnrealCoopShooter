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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn Info")
	TAssetSubclassOf<AMGunActor> Gun;
	virtual FPrimaryAssetId GetPrimaryAssetId() const override
	{
		return FPrimaryAssetId("Guns", GetFName());
	}	
};
