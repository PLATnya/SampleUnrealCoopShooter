
#pragma once
#include "CoreMinimal.h"
#include "MGunActor.h"
#include "Components/ActorComponent.h"
#include "MInventoryComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SAMPLEUNREALCOOPFPS_API UMInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMInventoryComponent();
	UPROPERTY(BlueprintReadOnly)
	TArray<class AMGunActor*> Guns;
	UPROPERTY(BlueprintReadWrite)
	int32 GunsLimit;
	UFUNCTION(BlueprintCallable,Category="Inventory")
	bool TryAddGun(AMGunActor* NewGun);
	UFUNCTION(BlueprintCallable,Category="Inventory")
	bool TryDropGun();

};
