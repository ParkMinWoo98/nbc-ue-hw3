#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelWaveDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FWaveData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float WaveDuration;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ItemCount;
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
