#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallingBomb.generated.h"

class USphereComponent;
class UDangerAreaComponent;

UCLASS()
class SPARTAPROJECT_API AFallingBomb : public AActor
{
	GENERATED_BODY()
	
public:
	AFallingBomb();

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& SweepResult);
	void Explode();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* Collision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* ExplosionCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UDangerAreaComponent* DangerArea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effect")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item | Effect")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mine")
	int32 ExplosionDamage;
};
