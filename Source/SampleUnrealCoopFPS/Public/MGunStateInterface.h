#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "MCharacterBase.h"
#include "MGunActor.h"
#include "MGunStateInterface.generated.h"




UCLASS()
class UMGunStateInterface : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void SetGun(AMGunActor* NewGun);
	UPROPERTY(EditAnywhere)
	AMGunActor* Gun;

	
	UFUNCTION()
	virtual void Config(const FVector Offset , const FVector OutOffset);
	
	UFUNCTION(BlueprintCallable)
    void Hide();
	UFUNCTION(BlueprintCallable)
	void Show();
	
};


UCLASS()
class SAMPLEUNREALCOOPFPS_API UMLeftGunState: public UMGunStateInterface{
	GENERATED_BODY()
	public:
	
	
   virtual void Config(const FVector Offset = FVector(70,-50,50) , const FVector OutOffset = FVector(70,-50,50));

	
};

UCLASS()
class SAMPLEUNREALCOOPFPS_API UMRightGunState:public UMGunStateInterface{
	GENERATED_BODY()
	public:
	
	
    virtual void Config(const FVector Offset = FVector(70,-50,50) , const FVector OutOffset =FVector(70,-50,50));
	
};
UCLASS()
class SAMPLEUNREALCOOPFPS_API UMCenterGunState:public UMGunStateInterface{
	GENERATED_BODY()
	public:
	
	
   virtual void Config(const FVector Offset = FVector(70,0,50) , const FVector OutOffset = FVector(70,-50,50));
	
};