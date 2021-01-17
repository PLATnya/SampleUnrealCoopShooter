// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.h"
#include "MGunStateInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"

#include "MGunActor.generated.h"

UCLASS()
class SAMPLEUNREALCOOPFPS_API AMGunActor : public AMInteractActor,  public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	AMGunActor();

protected:
	
	UAbilitySystemComponent* AbilitySystemComponent;
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category = "GAS")
	TArray<TSubclassOf<UGameplayAbility>> Abilities;

	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

public:
	UPROPERTY()
	class UMGunStateInterface *GunState;

	UPROPERTY()
	int32 MaxClipCount;
	UPROPERTY()
	int32 ClipCount;

	FName GunTypeName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	FGameplayTag WeaponTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	FGameplayTag ShootTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	FGameplayTag ReloadTag;
	
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	FGameplayTag AmmoType;

	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
	int32 GetClipCount ();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
	int32 GetMaxClipCount();
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void SetClipCount(int32 Count);
	UFUNCTION(BlueprintCallable, Category="Weapon")
    void SetMaxClipCount(int32 Count);
	
	//reload - AddCount = Clamp(reserve_ammo,0,MaxClipCount - ClipCount) 
	//ClipCount += AddCount
	//ReserveAmmo -= AddCount
	
	virtual void Tick(float DeltaTime) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	void SetAbilitySystemComponent(UAbilitySystemComponent* Asc);
	void AddAbilities();
	void RemoveAbilities();
};
