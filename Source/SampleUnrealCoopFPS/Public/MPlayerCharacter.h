// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MCharacterBase.h"
#include "MInventoryComponent.h"
#include "MPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLEUNREALCOOPFPS_API AMPlayerCharacter : public AMCharacterBase
{
	GENERATED_BODY()
	public:
	// Sets default values for this character's properties
	AMPlayerCharacter();

	protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
	class UMAttributeSetInventory* AmmoAttributeSet;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UMInventoryComponent* Inventory;


	UFUNCTION(BlueprintCallable,Category="Inventory")
	void ChangeWeapon(const int32 Index);


	
	
	void LookUp(float Value);
	void Turn(float Value);
	void MoveForward(float Value);
	void MoveRight(float Value);
};

