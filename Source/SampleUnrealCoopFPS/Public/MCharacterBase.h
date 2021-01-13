// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "MAttributeSetCharacter.h"
#include "MInteractActor.h"
#include "MCharacterBase.generated.h"




UCLASS()
class SAMPLEUNREALCOOPFPS_API AMCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()



protected:
	virtual void BeginPlay() override;

public:	
   	
    
   	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
   	class UAbilitySystemComponent* AbilitySystemComponent;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities | Attributes", meta = (AllowPrivateAccess = "true"))
    class UMAttributeSetCharacter* AttributeSet;
	
	
	AMCharacterBase();
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual void Tick(float DeltaTime) override;
	
	
	// Removes all CharacterAbilities. Can only be called by the Server. Removing on the Server will remove from Client too.
	
	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	UFUNCTION(BlueprintCallable, Category = "MCharacter")
    virtual bool IsAlive() const;
	UFUNCTION(BlueprintCallable, Category = "MCharacter|Attributes")
	float GetHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MCharacter|Attributes")
    float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MCharacter|Attributes")
	virtual void SetHealth(float Health);
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "GASShooter|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CharacterAbilities;

	UPROPERTY(BlueprintReadWrite)
	AMInteractActor* LeftHandHandler;
	UPROPERTY(BlueprintReadWrite)
	AMInteractActor* RightHandHandler;

	UFUNCTION(BlueprintCallable)
	bool GetInHand(AMInteractActor* InteractActor);
};
