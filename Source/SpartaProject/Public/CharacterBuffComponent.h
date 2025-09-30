#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterBuffComponent.generated.h"

class UBuff;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffAdded, UBuff*, Buff);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SPARTAPROJECT_API UCharacterBuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterBuffComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddBuff(UBuff* Buff);
	UBuff* FindBuffOfClass(TSubclassOf<UBuff> BuffClass) const;

	UPROPERTY(BlueprintAssignable, Category = "Buff")
	FOnBuffAdded OnBuffAdded;

protected:
	UPROPERTY()
	TArray<UBuff*> Buffs;
};
