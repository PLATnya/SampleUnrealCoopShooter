
#include "MGunStateInterface.h"



void UMGunStateInterface::SetGun(AMInteractActor* NewGun)
{
	Gun = NewGun;
}

AMInteractActor* UMGunStateInterface::GetGun() const
{
	return Gun;
}

void UMGunStateInterface::Config()
{
	Gun->SetActorRelativeLocation(Offset);
	
}

void UMGunStateInterface::Hide()
{
	Gun->SetActive(false);
}

void UMGunStateInterface::Show()
{
	Gun->SetActive(true);
}

void UMLeftGunState::Config()
{

	Offset = FVector(70,-50,-20);
	OutOffset = FVector(70,-50,-100);
	Super::Config();
}

void UMRightGunState::Config()
{
	Offset = FVector(70,50,-20);
	OutOffset = FVector(70,50,-100);
	Super::Config( );
}

void UMCenterGunState::Config()
{
	Offset = FVector(70,0,-20);
	OutOffset = FVector(70,0,-100);
	Super::Config();
}

