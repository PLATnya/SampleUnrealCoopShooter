// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerCharacter.h"
AMPlayerCharacter::AMPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AMPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &AMPlayerCharacter::Turn);

}

void AMPlayerCharacter::LookUp(float Value)
{
	if (IsAlive())
	{
		AddControllerPitchInput(Value);
	}
}


void AMPlayerCharacter::Turn(float Value)
{
	if (IsAlive())
	{
		AddControllerYawInput(Value);
	}
}


void AMPlayerCharacter::MoveForward(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMPlayerCharacter::MoveRight(float Value)
{
	if (IsAlive())
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}