// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "MAttributeSetCharacter.generated.h"



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMAttributeSetCharacter : public UAttributeSet
{
	GENERATED_BODY()
	public:
	UMAttributeSetCharacter();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UMAttributeSetCharacter, Health)
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AttributeTest")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UMAttributeSetCharacter, MaxHealth)
};
