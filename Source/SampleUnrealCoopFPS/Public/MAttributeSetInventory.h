// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MAttributeSetInventory.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
		GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMAttributeSetInventory : public UAttributeSet
{
	GENERATED_BODY()

	public:
	UMAttributeSetInventory();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromModifiers))
	FGameplayAttributeData ReservePistolAmmo;
	ATTRIBUTE_ACCESSORS(UMAttributeSetInventory, ReserveAvtoAmmo);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest", meta = (HideFromModifiers))
	FGameplayAttributeData ReserveAvtoAmmo;
	ATTRIBUTE_ACCESSORS(UMAttributeSetInventory, ReservePistolAmmo);
	
};
