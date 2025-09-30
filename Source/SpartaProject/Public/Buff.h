#pragma once
#include "CoreMinimal.h"
#include "Buff.generated.h"

class ASpartaCharacter;

UENUM(BlueprintType)
enum class EBuffStackType : uint8
{
	IgnoreIfExist				UMETA(DisplayName = "Ignore If Exist"),
	RefreshDuration				UMETA(DisplayName = "Refresh Duration"),
	AddDuration					UMETA(DisplayName = "Add Duration"),
	StackMultiple				UMETA(DisplayName = "Stack Multiple"),
};

UCLASS(Abstract)
class SPARTAPROJECT_API UBuff : public UObject
{
	GENERATED_BODY()

public:
	UBuff();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void Apply(ASpartaCharacter* Target);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void Tick(ASpartaCharacter* Target, float DeltaTime);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Buff")
	void Remove(ASpartaCharacter* Target);

	EBuffStackType GetStackType() const;
	int32 GetId() const;
	FName GetName() const;
	float GetDuration() const;
	float GetRemainTime() const;

	void SetId();
	void SetRemainTime(float NewRemainTime);
	void AddRemainTime(float AdditionalRemainTime);

protected:
	EBuffStackType BuffStackType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	int32 BuffId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	FName BuffName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	float Duration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float RemainTime;

	static int32 NextId;
};