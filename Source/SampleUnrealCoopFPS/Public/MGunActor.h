// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractActor.h"
#include "MGunStateInterface.h"
#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "GameplayTagContainer.h"

#include "MGunActor.generated.h"


UENUM(Blueprintable)
enum class EGunActions:uint8
{
	SHOOT,
    RELOAD
};
UCLASS()	
class SAMPLEUNREALCOOPFPS_API AMGunActor : public AMInteractActor,  public IAbilitySystemInterface
{
	GENERATED_BODY()
	UPROPERTY()
	int32 MaxClipCount;
	UPROPERTY()
	int32 ClipCount;
	
	UPROPERTY()
	UAbilitySystemComponent* AbilitySystemComponent;
	


	
protected:
		
	UPROPERTY(EditDefaultsOnly, Category = "GAS")
	TMap<EGunActions,TSubclassOf<UGameplayAbility>> Abilities;
	UPROPERTY(BlueprintReadOnly, Category = "GAS")
	TMap<EGunActions,FGameplayAbilitySpecHandle> AbilitySpecHandles;
	
public:
	AMGunActor();

	UFUNCTION(BlueprintCallable, Category="GAS|Weapon")
	void Shoot();
	UFUNCTION(BlueprintCallable, Category="GAS|Weapon")
    void Reload();
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "GAS|Weapon")
	TMap<FName,FGameplayTag> WeaponTagsMap;
	UPROPERTY(BlueprintReadWrite)
	class UMGunStateInterface *GunState;
	
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
	int32 GetClipCount ();
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Weapon")
	int32 GetMaxClipCount();
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void SetClipCount(int32 Count);
	UFUNCTION(BlueprintCallable, Category="Weapon")
    void SetMaxClipCount(int32 Count);
	
	virtual bool TryGet(AActor* Parent = nullptr) override;
	virtual bool TryDrop() override;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable, Category = "GAS")
	void SetAbilitySystemComponent(UAbilitySystemComponent* Asc);
	UFUNCTION(BlueprintCallable, Category= "GAS")
	void AddAbilities();
	UFUNCTION(BlueprintCallable, Category= "GAS")
	void RemoveAbilities();
};
