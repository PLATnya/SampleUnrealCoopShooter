#include "MPlayerControllerBase.h"

#include "MCharacterBase.h"

void AMPlayerControllerBase::AcknowledgePossession(APawn* P)
{
	Super::AcknowledgePossession(P);

	AMCharacterBase* CharacterBase = Cast<AMCharacterBase>(P);
	if (CharacterBase)
	{
		CharacterBase->GetAbilitySystemComponent()->InitAbilityActorInfo(CharacterBase, CharacterBase);
	}

	//...
}