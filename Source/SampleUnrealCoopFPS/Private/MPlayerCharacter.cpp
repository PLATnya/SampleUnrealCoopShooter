
#include "MPlayerCharacter.h"

AMPlayerCharacter::AMPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	Inventory = CreateDefaultSubobject<UMInventoryComponent>("InventoryOfGuns");
	AmmoAttributeSet = CreateDefaultSubobject<UMAttributeSetInventory>("AmmoAttributeSet");
}

/*
void AMPlayerCharacter::ChangeWeapon(const int32 Index)
{
	if(Index>=Inventory->Guns.Num())
		return;
	FGameplayTagContainer AbilityTagsToCancel;
	AMGunActor* Gun = Inventory->Guns[Index];
	AMGunActor* MainGun = Cast<AMGunActor>(MainHandler.InteractHandler);
	
	AMGunActor* AltGun = Cast<AMGunActor>(AltHandler.InteractHandler);
	const bool HandlerValid = IsValid(MainGun);
	const bool AltHandlerValid = IsValid(AltGun);

	if(HandlerValid)
	{
		MainGun->GunState->Hide();
		MainHandler.InteractHandler = nullptr;
		
		AbilityTagsToCancel.AddTag(MainGun->WeaponTagsMap["WeaponTag"]);
	}
	if(Gun!=MainGun)
	{
		if(Gun == AltGun)
		{
			AltHandler.InteractHandler = nullptr;
		}else
		{
			MainHandler.InteractHandler = Gun;
		}
	}
	if(Gun->bTwoHanded)
	{
		if(AltHandlerValid)
		{
			AltGun->GunState->Hide();
			AltHandler.InteractHandler = nullptr;
			AbilityTagsToCancel.AddTag(AltGun->WeaponTagsMap["WeaponTag"]);
			if(Gun!=MainGun)
			{
				AltHandler.InteractHandler = Gun;
			}
		}
		Gun->GunState = NewObject<UMCenterGunState>();
		Gun->GunState->SetGun(Gun);
		Gun->GunState->Config();
		Gun->GunState->Show();
	}else
	{
		if(Gun!=MainGun)
		{
			switch (MainHandler.Hand)
			{
			case EHand::LEFT:
				Gun->GunState = NewObject<UMLeftGunState>();
				break;
			case EHand::RIGHT:
				Gun->GunState = NewObject<UMRightGunState>();
				break;
			}
			Gun->GunState->SetGun(Gun);
			Gun->GunState->Config();
			Gun->GunState->Show();
		}
	}
	
}*/

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
	AddMovementInput(GetActorForwardVector(),Value);
}

void AMPlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
