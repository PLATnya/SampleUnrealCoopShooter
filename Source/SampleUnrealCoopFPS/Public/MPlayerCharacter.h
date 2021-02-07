// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "MAttributeSetInventory.h"
#include "MCharacterBase.h"
#include "MInventoryComponent.h"
#include "MSpringArmComponent.h"

#include "MPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEUNREALCOOPFPS_API AMPlayerCharacter : public AMCharacterBase
{
	GENERATED_BODY()
	
	void LookUp(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
	UPROPERTY()
	UMAttributeSetInventory* AmmoAttributeSet;

	protected:
	UPROPERTY(Category=Inventory, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	class UMInventoryComponent* Inventory;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	public:
	AMPlayerCharacter();

	/*
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UMSpringArmComponent* LeftArm;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	class UMSpringArmComponent* RightArm;
	*/
	
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable,Category = Character)
	void CheckLedge(int32 MaxTraceCount);
	UFUNCTION(BlueprintCallable,Category="Inventory")
	void ChangeWeapon(const int32 Index);
	

};

