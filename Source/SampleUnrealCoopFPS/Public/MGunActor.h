// Fill out your copyright notice in the Description page of Project Settings.

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
	
	UFUNCTION()
	void OnReloadEnd(const FAbilityEndedData& Data);

	
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> AddAmmoEffect;
	
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere , BlueprintReadOnly)
	USkeletalMeshComponent* SkeletalMesh;

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UCameraShakeSourceComponent* ShakeSource;
	
	AMGunActor();
	UPROPERTY(BlueprintReadWrite, Category="Weapon")
	bool bCanStartShoot;
	
	UFUNCTION(BlueprintCallable, Category = "GAS")
	UGameplayEffect* MakeAmmoEffect(float Magnitude);
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "GAS")
	FGameplayAttribute ReserveAmmoAttribute;

	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FVector SpawnPoint;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category="Weapon")
	void Shoot(FName SocketName = "Root");
	virtual void Shoot_Implementation(FName SocketName = "Root");

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category="Weapon")
	void EndShoot();
	
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
	void AddAbilities(int32 InLevel, FGameplayTag HandTag);
	UFUNCTION(BlueprintCallable, Category= "GAS")
	void RemoveAbilities();
};
