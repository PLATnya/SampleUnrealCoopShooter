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

	AMGunActor* Gun = Inventory->Guns[Index];
	UE_LOG(LogTemp,Display,TEXT("new gun is: %s"),*GetNameSafe(Gun));
	AMGunActor* MainGun = Cast<AMGunActor>(MainHandler);
	if(Index>=Inventory->Guns.Num())
		return;

	const bool bTwoHanded = Gun->bInLeftHand&&Gun->bInRightHand;
	AMGunActor* AltGun = Cast<AMGunActor>(AltHandler);
	const bool HandlerValid = IsValid(MainGun);
	const bool ALtHandlerValid = IsValid(AltGun);
	if(bTwoHanded)
	{
		if(HandlerValid)
		{
			MainGun->GunState->Hide();
			MainHandler = nullptr;
			
			if(MainGun == Gun)
			{
				AltHandler = nullptr;
				return;
			}
		}
		if(ALtHandlerValid) AltGun->GunState->Hide();
		AltHandler = nullptr;
		UMCenterGunState* NewState = NewObject<UMCenterGunState>();
		Gun->GunState = NewState;
		Gun->GunState->SetGun(Gun);
		MainHandler = Gun;
		AltHandler = Gun;
		NewState->Show();
		Gun->GunState->Show();
	}else
	{
		if(HandlerValid )
		{
			MainGun->GunState->Hide();
			MainHandler = nullptr;
			if(MainGun == Gun)
			{
				return;
			}
		}
		if(ALtHandlerValid&& AltGun==Gun)
		{
			AltGun->GunState->Hide();
			AltHandler = nullptr;
		}
		UMLeftGunState* NewState = NewObject<UMLeftGunState>();
		Gun->GunState = NewState;
		Gun->GunState->SetGun(Gun);
		NewState->Config();
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
