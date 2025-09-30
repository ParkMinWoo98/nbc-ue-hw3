#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "BlindBuff.generated.h"

class ASpartaCharacter;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class SPARTAPROJECT_API UBlindBuff : public UBuff
{
	GENERATED_BODY()
	
public:
	UBlindBuff();

	void Apply_Implementation(ASpartaCharacter* Target);
	void Remove_Implementation(ASpartaCharacter* Target);
};
