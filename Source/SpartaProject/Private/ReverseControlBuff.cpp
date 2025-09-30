#include "ReverseControlBuff.h"
#include "SpartaCharacter.h"
#include "CharacterAttribute.h"

UReverseControlBuff::UReverseControlBuff()
{
	BuffStackType = EBuffStackType::RefreshDuration;
}

void UReverseControlBuff::Apply_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;

	Super::Apply_Implementation(Target);
	if (UCharacterAttribute* Attribute = Target->FindComponentByClass<UCharacterAttribute>())
	{
		Attribute->SetReverseControl(true);
	}
}

void UReverseControlBuff::Remove_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;

	Super::Remove_Implementation(Target);
	if (UCharacterAttribute* Attribute = Target->FindComponentByClass<UCharacterAttribute>())
	{
		Attribute->SetReverseControl(false);
	}
}