// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "MSpringArmComponent.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()
public:
	UMSpringArmComponent();
	
	UPROPERTY(BlueprintReadWrite)
	class UMGunStateInterface *GunState;
};
