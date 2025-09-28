#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"

UCLASS()
class SPARTAPROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
    AMineItem();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    void ActivateItem_Implementation(AActor* Activator);

    void Explode();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    USphereComponent* ExplosionCollision;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effect")
    UParticleSystem* ExplosionParticle;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effect")
    USoundBase* ExplosionSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionDelay;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    float ExplosionRadius;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
    int32 ExplosionDamage;

private:
    FTimerHandle ExplosionTimerHandle;
    bool bHasExploded;
};
