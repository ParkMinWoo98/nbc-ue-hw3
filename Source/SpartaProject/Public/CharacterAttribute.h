#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterAttribute.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPARTAPROJECT_API UCharacterAttribute : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacterAttribute();

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetMaxHealth() const;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
	float ApplyDamage(float Damage);
	void OnDeath();
	void UpdateOverheadHp();

	void AddSpeedModifier(int32 BuffId, float Modifier);
	void RemoveSpeedModifier(int32 BuffId);
	void RecalculateSpeed();
	void Sprint(bool bSprinting);

	bool GetReverseControl() const;
	void SetReverseControl(bool bReverse);

protected:
	virtual void BeginPlay() override;
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float NormalSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float SprintSpeedMultiplier;
	bool bIsSprinting;

	bool bReverseControl;

	// Buff Modifier - key: BuffId
	TMap<int32, float> SpeedModifiers;
};
