#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DangerAreaComponent.generated.h"

UENUM(BlueprintType)
enum class DangerAreaEffectType : uint8
{
	None				UMETA(DisplayName = "None"),
	Fill				UMETA(DisplayName = "Fill"),
	FadeIn				UMETA(DisplayName = "FadeIn"),
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SPARTAPROJECT_API UDangerAreaComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UDangerAreaComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Spawn(const FVector& Size, const FVector& Location, const FRotator& Rotation = FRotator(-90.0f, 0.0f, 0.0f), float Duration = 0.0f, DangerAreaEffectType InType = DangerAreaEffectType::None, bool bNewEndAfterDuration = false);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area | Setting")
	UMaterial* MaterialArea;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area | Setting")
	UMaterialInstanceDynamic* MaterialAreaInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Area | Setting")
	DangerAreaEffectType Type;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area| Setting")
	UDecalComponent* Decal;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area")
	FVector DecalSize;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area")
	float DecalDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area")
	float DecalTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Area")
	bool bEndAfterDuration;
};
