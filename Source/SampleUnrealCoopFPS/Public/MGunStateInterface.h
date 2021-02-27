#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MGunStateInterface.generated.h"



UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UMGunStateInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class IMGunStateInterface 
{
	GENERATED_IINTERFACE_BODY()

	virtual void Config() = 0;
    virtual void Hide() =0 ;
	virtual void Show() = 0;
};

