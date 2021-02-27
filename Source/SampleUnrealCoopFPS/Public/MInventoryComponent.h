
#pragma once
#include "CoreMinimal.h"
#include "MGunActor.h"
#include "MSpringArmComponent.h"
#include "Components/ActorComponent.h"
#include "MInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLEUNREALCOOPFPS_API UMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int32 GunsLimit;
	UPROPERTY()
	TArray<class AMGunActor*> Guns;
	UPROPERTY()
	UUserWidget* ScreenAmmoWidget;
	protected:
	virtual void BeginPlay() override;
	public:
	UMInventoryComponent();
	UPROPERTY(Category="Widget", EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> AmmoWidget;

	UFUNCTION(BlueprintCallable, Category="Inventory")
	UMSpringArmComponent* AttachToArm(int32 Hand, AMGunActor* GunActor);
	UFUNCTION(BlueprintCallable,Category="Inventory")
	bool TryAddGun(AMGunActor* NewGun);
	UFUNCTION(BlueprintCallable,Category="Inventory")
	bool TryDropGun();
	UFUNCTION(BlueprintCallable,Category="Inventory")
	FORCEINLINE AMGunActor* GetGun(int32 Index) const{ return Index>=GunsLimit?nullptr:Guns[Index]; }
	FORCEINLINE int32 GetGunsCount()const {return static_cast<int32>(Guns.Num());}
};
