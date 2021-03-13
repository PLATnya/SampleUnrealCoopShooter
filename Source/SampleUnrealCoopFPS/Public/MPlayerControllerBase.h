// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEUNREALCOOPFPS_API AMPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	virtual void AcknowledgePossession(APawn* P) override;
};
