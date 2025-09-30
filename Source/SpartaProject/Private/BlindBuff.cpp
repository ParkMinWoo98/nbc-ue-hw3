#include "BlindBuff.h"
#include "SpartaCharacter.h"

UBlindBuff::UBlindBuff()
{
	BuffStackType = EBuffStackType::RefreshDuration;
}

void UBlindBuff::Apply_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;

	Super::Apply_Implementation(Target);
	Target->AddAilment(ECharacterAilment::Blind);
}

void UBlindBuff::Remove_Implementation(ASpartaCharacter* Target)
{
	if (!Target) return;

	Super::Remove_Implementation(Target);
	Target->RemoveAilment(ECharacterAilment::Blind);
}