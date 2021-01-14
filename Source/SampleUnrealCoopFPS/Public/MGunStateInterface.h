#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MCharacterBase.h"
#include "MGunActor.h"
#include "MGunStateInterface.generated.h"



class UMGunStateInterface;
UCLASS()
class UMGunStateInterface : public UObject
{
	GENERATED_BODY()
	AMGunActor* Gun;
public:
	virtual void SetGun(AMGunActor* Gun);
	
	void Config( AMCharacterBase* Character, const FVector Offset, const FVector OutOffset);
	virtual void Hide();
	virtual void Show();
	
};


UCLASS()
class SAMPLEUNREALCOOPFPS_API UMLeftGunState: public UMGunStateInterface{
	GENERATED_BODY()
	public:
	void Config( AMCharacterBase* Character);
};

UCLASS()
class SAMPLEUNREALCOOPFPS_API UMRightGunState:public UMGunStateInterface{
	GENERATED_BODY()
	public:
	void Config( AMCharacterBase* Character);

};
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMCenterGunState:public UMGunStateInterface{
	GENERATED_BODY()
	public:
	void Config( AMCharacterBase* Character);

};