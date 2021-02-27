﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.h"
#include "MGunStateInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"
#include "MGameplayAbility.h"
#include "Components/Image.h"
#include "GameFramework/SpringArmComponent.h"



#include "MGunActor.generated.h"


UENUM(Blueprintable)
enum class EGunActions:uint8
{
	SHOOT,
    RELOAD
};

UCLASS()
class SAMPLEUNREALCOOPFPS_API UMClipHolder:public UObject{

	GENERATED_BODY()
	UPROPERTY()
	int32 MaxClipCount;
	UPROPERTY()
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




UCLASS()	
class SAMPLEUNREALCOOPFPS_API AMGunActor : public AMInteractActor,  public IAbilitySystemInterface,public IMGunStateInterface
{
	GENERATED_BODY()
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraShakeSourceComponent* ShakeSource;
	
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	USpringArmComponent* ArmComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* Icon;
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> Projectile;
	
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TMap<EGunActions,TSubclassOf<UMGameplayAbility>> Abilities;
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TMap<EGunActions,FGameplayAbilitySpecHandle> AbilitySpecHandles;
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly, Category = "Anim")
	TMap<EGunActions,UAnimMontage*> ActionMontages;
	
public:
	
	
	
	AMGunActor();

	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
    virtual void Hide() override;
	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
    virtual void Show() override;
	virtual void Config() override;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	UMClipHolder* ClipHolder;
	UFUNCTION(BlueprintCallable, Category="Weapon")
    void Shoot();
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category="Weapon")
	void EndShoot();
	UFUNCTION(BlueprintCallable, Category="GAS|Weapon")
    void Reload();

	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	TMap<FName,FGameplayTag> WeaponTagsMap;

	
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void SetAbilitySystemComponent(UAbilitySystemComponent* Asc);
	UFUNCTION(BlueprintCallable, Category= "GAS")
	void AddAbilities(int32 InLevel);
	UFUNCTION(BlueprintCallable, Category= "GAS")
	void RemoveAbilities();
};
