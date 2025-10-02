﻿#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "SpartaGameState.generated.h"

class ULevelWaveDataAsset;
class AFallingBomb;

UCLASS()
class SPARTAPROJECT_API ASpartaGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ASpartaGameState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, Category = "Score")
	int32 GetScore() const;
	UFUNCTION(BlueprintCallable, Category = "Score")
	void AddScore(int32 Amount);
	UFUNCTION(BlueprintCallable, Category = "Score")
	void StartLevel();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void EndLevel();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void StartWave();
	UFUNCTION(BlueprintCallable, Category = "Score")
	void EndWave();

	void OnWaveTimeUp();
	void OnGameOver();
	void OnCoinCollected();
	void UpdateHUD();

	void SpawnBomb();
	void AnnounceStartWaveHUD();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int32 Score;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Coin")
	int32 CollectedCoinCount;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentLevelIndex;
	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly, Category = "Level")
	int32 CurrentWaveIndex;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	ULevelWaveDataAsset* LevelData;

private:
	FTimerHandle LevelTimerHandle;
	FTimerHandle HUDUpdateTimerHandle;
	FTimerHandle FallingBombTimerHandle;
};
