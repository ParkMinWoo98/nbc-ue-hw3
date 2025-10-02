#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelWaveDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaveDuration = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BombSpawnInterval = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AActor> BombClass;
};

USTRUCT(BlueprintType)
struct FLevelWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName MapName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FWaveData> WaveDatas;
};

UCLASS()
class SPARTAPROJECT_API ULevelWaveDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FLevelWave> LevelWaves;
};
