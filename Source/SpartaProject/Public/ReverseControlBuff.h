#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "ReverseControlBuff.generated.h"

class ASpartaCharacter;

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class SPARTAPROJECT_API UReverseControlBuff : public UBuff
{
	GENERATED_BODY()

public:
	UReverseControlBuff();

	void Apply_Implementation(ASpartaCharacter* Target);
	void Remove_Implementation(ASpartaCharacter* Target);
};
