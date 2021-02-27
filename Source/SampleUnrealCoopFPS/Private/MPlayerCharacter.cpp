
#include "MPlayerCharacter.h"

AMPlayerCharacter::AMPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Inventory = CreateDefaultSubobject<UMInventoryComponent>("InventoryOfGuns");
	AmmoAttributeSet = CreateDefaultSubobject<UMAttributeSetInventory>("AmmoAttributeSet");

	LeftArm = CreateDefaultSubobject<UMSpringArmComponent>("LeftSpringArm");
	RightArm = CreateDefaultSubobject<UMSpringArmComponent>("RightSpringArm");
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
	if(Index>=Inventory->GetGunsCount())
		return;
	FGameplayTagContainer AbilityTagsToCancel;
	AMGunActor* Gun = Inventory->GetGun(Index);
	AMGunActor* MainGun = Cast<AMGunActor>(GetMainHandler().InteractHandler);
	
	AMGunActor* AltGun = Cast<AMGunActor>(GetAltHandler().InteractHandler);
	const bool HandlerValid = IsValid(MainGun);
	const bool ALtHandlerValid = IsValid(AltGun);
	if(Gun->IsTwoHanded())
	{
		if(MainGun == Gun)
		{
			if(HandlerValid)
			{
				MainGun->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				GetMainHandler().InteractHandler = nullptr;
				GetAltHandler().InteractHandler = nullptr;
				GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			}
			
		}else{
			if(HandlerValid)
			{
				MainGun->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				GetMainHandler().InteractHandler = nullptr;
			}
			if(ALtHandlerValid)
			{
				AltGun->Hide();
				AbilityTagsToCancel.AddTag(AltGun->WeaponTagsMap["WeaponTag"]);
			}
			GetAltHandler().InteractHandler = nullptr;
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);

			//
			Inventory->AttachToArm(0,Gun);
			
		
			GetMainHandler().InteractHandler = Gun;
			GetAltHandler().InteractHandler = Gun;
			Gun->Show();
			Gun->WeaponTagsMap["HandTag"] = GetMainHandler().HandTag;
		}
		

		
	}else
	{
		
		if(!(MainGun == Gun&&HandlerValid))
		{
			if(HandlerValid )
			{
				MainGun->Hide();
				AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
				GetMainHandler().InteractHandler = nullptr;
			}
			if(ALtHandlerValid&& AltGun==Gun)
			{
				AltGun->Hide();
				AbilityTagsToCancel.AddTag(AltGun->WeaponTagsMap["WeaponTag"]);
				GetAltHandler().InteractHandler = nullptr;
			}
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);

			Inventory->AttachToArm(GetMainHandler().Hand,Gun);
			Gun->Config();
			Gun->Show();
			Gun->WeaponTagsMap["HandTag"] = GetMainHandler().HandTag;
			GetMainHandler().InteractHandler = Gun;
		}else if(MainGun == Gun&&HandlerValid)
		{
			AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
			GetAbilitySystemComponent()->CancelAbilities(&AbilityTagsToCancel);
			MainGun->Hide();
			GetMainHandler().InteractHandler = nullptr;
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
