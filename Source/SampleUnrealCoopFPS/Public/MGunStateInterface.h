#pragma once
#include "CoreMinimal.h"
#include "MCharacterBase.h"
#include "MGunStateInterface.generated.h"

UCLASS()
class UMGunStateInterface : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	AMInteractActor* Gun;
protected :
	UPROPERTY(EditInstanceOnly, Category="Interact|GunState")
	FVector Offset;
	UPROPERTY(EditInstanceOnly, Category="Interact|GunState")
	FVector OutOffset;
public:
	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
	void SetGun(AMInteractActor* NewGun); 
	UFUNCTION(BlueprintCallable,BlueprintPure, Category="Interact|GunState")
	AMInteractActor* GetGun() const;
	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
	virtual void Config();
	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
    void Hide();
	UFUNCTION(BlueprintCallable, Category="Interact|GunState")
	void Show();
};

UCLASS()
class SAMPLEUNREALCOOPFPS_API UMLeftGunState: public UMGunStateInterface{
	GENERATED_BODY()

	public:
    virtual void Config() override;	
};
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMRightGunState:public UMGunStateInterface{
	GENERATED_BODY()
	
	public:
    virtual void Config() override;
};
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMCenterGunState:public UMGunStateInterface{
	GENERATED_BODY()

	public:
    virtual void Config() override;
};