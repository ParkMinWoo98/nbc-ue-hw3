#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTAPROJECT_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnVolume();

	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	AActor* SpawnRandomItem();

protected:
	FItemSpawnRow* GetRandomItem() const;
	FVector GetRandomPointInVolume() const;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning")
	UBoxComponent* SpawningBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning")
	UDataTable* ItemDataTable;
};
