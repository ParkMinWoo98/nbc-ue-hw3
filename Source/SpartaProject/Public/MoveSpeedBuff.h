#pragma once

#include "CoreMinimal.h"
#include "Buff.h"
#include "MoveSpeedBuff.generated.h"

UCLASS(Blueprintable, EditInlineNew, DefaultToInstanced)
class SPARTAPROJECT_API UMoveSpeedBuff : public UBuff
{
	GENERATED_BODY()

public:
	UMoveSpeedBuff();

	void Apply_Implementation(ASpartaCharacter* Target);
	void Remove_Implementation(ASpartaCharacter* Target);

	float GetSpeedMultiplier() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float SpeedMultiplier;
};
