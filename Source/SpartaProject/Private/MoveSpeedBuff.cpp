#include "MoveSpeedBuff.h"
#include "SpartaCharacter.h"
#include "CharacterAttribute.h"

UMoveSpeedBuff::UMoveSpeedBuff()
{
	BuffStackType = EBuffStackType::StackMultiple;
}

void UMoveSpeedBuff::Apply_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;
	
	Super::Apply_Implementation(Target);
	if (UCharacterAttribute* Attribute = Target->FindComponentByClass<UCharacterAttribute>())
	{
		if (SpeedMultiplier <= 0.0f) return;

		Attribute->AddSpeedModifier(BuffId, SpeedMultiplier);
		Attribute->RecalculateSpeed();
	}
}

void UMoveSpeedBuff::Remove_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;

	Super::Remove_Implementation(Target);
	if (UCharacterAttribute* Attribute = Target->FindComponentByClass<UCharacterAttribute>())
	{
		Attribute->RemoveSpeedModifier(BuffId);
		Attribute->RecalculateSpeed();
	}
}

float UMoveSpeedBuff::GetSpeedMultiplier() const
{
	return SpeedMultiplier;
}
