#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "MAttributeSetCharacter.h"
#include "GameplayAbilitySet.h"
#include "MInteractActor.h"
#include "MCharacterBase.generated.h"

UENUM()
enum EHand
{
	LEFT,
	RIGHT
};

USTRUCT(BlueprintType)
struct FHandler
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	AMInteractActor* InteractHandler;
	EHand Hand;
};

UCLASS()
class SAMPLEUNREALCOOPFPS_API AMCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities", meta = (AllowPrivateAccess = "true"))
	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY()
	class UMAttributeSetCharacter* AttributeSet;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "MCharacter|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> CharacterAbilities;
public:	
	AMCharacterBase();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UFUNCTION(BlueprintCallable)
	virtual void AddCharacterAbilities();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "MCharacter")
    virtual bool IsAlive() const;
	UFUNCTION(BlueprintCallable, BlueprintPure,Category = "MCharacter|Attributes")
	float GetHealth() const; 
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "MCharacter|Attributes")
    float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "MCharacter|Attributes")
	virtual void SetHealth(float Health);
	UFUNCTION(BlueprintCallable)
    void SwapHandlers();
	
	UPROPERTY(BlueprintReadOnly)
	FHandler MainHandler;
	UPROPERTY(BlueprintReadOnly)
	FHandler AltHandler;	
};
