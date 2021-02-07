
#include "MPlayerCharacter.h"

AMPlayerCharacter::AMPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Inventory = CreateDefaultSubobject<UMInventoryComponent>("InventoryOfGuns");
	AmmoAttributeSet = CreateDefaultSubobject<UMAttributeSetInventory>("AmmoAttributeSet");
	/*
	LeftArm = CreateDefaultSubobject<UMSpringArmComponent>("LeftArm");
	RightArm = CreateDefaultSubobject<UMSpringArmComponent>("RightArm");
	*/
	
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
	if(Index>=Inventory->Guns.Num())
		return;
	FGameplayTagContainer AbilityTagsToCancel;
	AMGunActor* Gun = Inventory->Guns[Index];
	AMGunActor* MainGun = Cast<AMGunActor>(MainHandler.InteractHandler);
	
	AMGunActor* AltGun = Cast<AMGunActor>(AltHandler.InteractHandler);
	const bool HandlerValid = IsValid(MainGun);
	const bool ALtHandlerValid = IsValid(AltGun);
	if(Gun->bTwoHanded)
	{
		if(MainGun == Gun)
		{
			if(HandlerValid)
			{
				MainGun->GunState->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				MainHandler.InteractHandler = nullptr;
				AltHandler.InteractHandler = nullptr;
				GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			}
			
		}else{
			if(HandlerValid)
			{
				MainGun->GunState->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				MainHandler.InteractHandler = nullptr;
			}
			if(ALtHandlerValid)
			{
				AltGun->GunState->Hide();
				AbilityTagsToCancel.AddTag(AltGun->WeaponTagsMap["WeaponTag"]);
			}
			AltHandler.InteractHandler = nullptr;
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			
			Gun->GunState = NewObject<UMCenterGunState>();
			Gun->GunState->SetGun(Gun);
			MainHandler.InteractHandler = Gun;
			AltHandler.InteractHandler = Gun;
			Gun->GunState->Show();
			Gun->GunState->Show();
			Gun->WeaponTagsMap["HandTag"] = MainHandler.HandTag;
		}
		

		
	}else
	{
		
		if(!(MainGun == Gun&&HandlerValid))
		{
			if(HandlerValid )
			{
				MainGun->GunState->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				MainHandler.InteractHandler = nullptr;
			}
			if(ALtHandlerValid&& AltGun==Gun)
			{
				AltGun->GunState->Hide();
				AbilityTagsToCancel.AddTag(AltGun->WeaponTagsMap["WeaponTag"]);
				AltHandler.InteractHandler = nullptr;
			}
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			
			switch (MainHandler.Hand)
			{
			case 0:
				
				Gun->GunState =NewObject<UMLeftGunState>();
				Gun->GunState->SetGun(Gun);
				Gun->GunState->Config();
				Gun->GunState->Show();
				break;
			case 1:
				Gun->GunState =NewObject<UMRightGunState>();
				Gun->GunState->SetGun(Gun);
				Gun->GunState->Config();
				Gun->GunState->Show();
				break;
				
			}
			Gun->WeaponTagsMap["HandTag"] = MainHandler.HandTag;
			MainHandler.InteractHandler = Gun;
		}else if(MainGun == Gun&&HandlerValid)
		{
			AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			MainGun->GunState->Hide();
			MainHandler.InteractHandler = nullptr;
		
		}
		
		
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
	if(Value >0) CheckLedge(4);
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
