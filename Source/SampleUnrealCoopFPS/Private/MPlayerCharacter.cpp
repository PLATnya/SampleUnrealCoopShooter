// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerCharacter.h"
AMPlayerCharacter::AMPlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Inventory = CreateDefaultSubobject<UMInventoryComponent>("InventoryOfGuns");
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

void AMPlayerCharacter::ChangeWeapon(const int32 Index)
{
	AMGunActor* MainGun = Cast<AMGunActor>(MainHandler);
	if(!MainGun) return;
	if(Index>=Inventory->Guns.Num()) return;
	AMGunActor* AltGun = Cast<AMGunActor>(AltHandler);
	
	FSetElementId SetIndex;
	AMGunActor* Gun = Inventory->Guns[SetIndex.FromInteger(Index)];
	const bool bTwoHanded = Gun->bInLeftHand&&Gun->bInRightHand;
	const bool HandlerValid = IsValid(MainGun);
	const bool ALtHandlerValid = IsValid(AltGun);
	if(bTwoHanded)
	{
		
		if(MainGun == Gun)
		{
			MainGun->GunState->Hide();
			MainHandler = nullptr;
			AltHandler = nullptr;
			return;
		}
		if(HandlerValid) MainGun->GunState->Hide();
		if(ALtHandlerValid) AltGun->GunState->Hide();
		Gun->GunState = NewObject<UMCenterGunState>();
		MainHandler = Gun;
		AltHandler = Gun;
		Gun->GunState->Show();
	}else
	{
		if(MainGun == Gun)
		{
			MainGun->GunState->Hide();
			MainHandler = nullptr;
			return;
		}
		if(AltGun==Gun)
		{
			AltGun->GunState->Hide();
			AltHandler = nullptr;
		}
		Gun->GunState = NewObject<UMLeftGunState>();
		Gun->GunState->Show();
		MainHandler = Gun;
	}
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
	AddControllerYawInput(Value);
}

void AMPlayerCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
