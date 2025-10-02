#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "SpartaPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "LevelWaveDataAsset.h"

ASpartaGameState::ASpartaGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	CurrentLevelIndex = 0;
	CurrentWaveIndex = 0;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&ASpartaGameState::UpdateHUD,
		0.1f,
		true);
}

int32 ASpartaGameState::GetScore() const
{
	return Score;
}

void ASpartaGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			SpartaGameInstance->AddToScore(Amount);
		}
	}
}

void ASpartaGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			CurrentLevelIndex = SpartaGameInstance->CurrentLevelIndex;
		}
	}

	CurrentWaveIndex = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	StartWave();
}

void ASpartaGameState::EndLevel()
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			AddScore(Score);
			CurrentLevelIndex++;
			SpartaGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= LevelData->LevelWaves.Num())
	{
		OnGameOver();
		return;
	}

	if (LevelData->LevelWaves.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelData->LevelWaves[CurrentLevelIndex].MapName);
	}
	else
	{
		OnGameOver();
	}
}

void ASpartaGameState::StartWave()
{
	GetWorldTimerManager().ClearTimer(FallingBombTimerHandle);
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = LevelData->LevelWaves[CurrentLevelIndex].WaveDatas[CurrentWaveIndex].ItemCount;
	if (FoundVolumes.Num() > 0)
	{
		if (ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]))
		{
			AActor* SpawnedCoin= SpawnVolume->SpawnRandomItem(ACoinItem::StaticClass());
			SpawnedCoinCount++;
			for (int32 i = 1; i < ItemToSpawn; i++)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	SpawnBomb();
	GetWorldTimerManager().SetTimer(
		FallingBombTimerHandle,
		this,
		&ASpartaGameState::SpawnBomb,
		LevelData->LevelWaves[CurrentLevelIndex].WaveDatas[CurrentWaveIndex].BombSpawnInterval,
		true);
	AnnounceStartWaveHUD();
	UpdateHUD();
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnWaveTimeUp,
		LevelData->LevelWaves[CurrentLevelIndex].WaveDatas[CurrentWaveIndex].WaveDuration,
		false);

	GEngine->AddOnScreenDebugMessage(
		-1,
		2.0f,
		FColor::Green,
		FString::Printf(TEXT("Level %d, Wave %d Start!, Spawned %d Coin"), CurrentLevelIndex + 1, CurrentWaveIndex + 1, SpawnedCoinCount));
}

void ASpartaGameState::EndWave()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);
	if (++CurrentWaveIndex >= LevelData->LevelWaves[CurrentLevelIndex].WaveDatas.Num())
	{
		EndLevel();
	}
	else
	{
		StartWave();
	}
}

void ASpartaGameState::OnWaveTimeUp()
{
	EndWave();
}

void ASpartaGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			SpartaPlayerController->SetPause(true);
			SpartaPlayerController->ShowGameOverMenu();
		}
	}
}

void ASpartaGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);
	
	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndWave();
	}
}

void ASpartaGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = FMath::Max(GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle), 0.0f);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance);
						if (SpartaGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), SpartaGameInstance->TotalScore)));
						}
					}
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Level: %d"), CurrentLevelIndex + 1)));
				}

				if (UTextBlock* LevelIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					LevelIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d / %d"), CurrentWaveIndex + 1, LevelData->LevelWaves[CurrentLevelIndex].WaveDatas.Num())));
				}
			}
		}
	}
}

void ASpartaGameState::SpawnBomb()
{
	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);
	if (FoundVolumes.Num() > 0)
	{
		ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
		if (SpawnVolume)
		{
			AActor* SpawnedActor = SpawnVolume->SpawnItem(LevelData->LevelWaves[CurrentLevelIndex].WaveDatas[CurrentWaveIndex].BombClass);
		}
	}
}

void ASpartaGameState::AnnounceStartWaveHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (ASpartaPlayerController* SpartaPlayerController = Cast<ASpartaPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				if (UTextBlock* BombText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("AnnounceWave"))))
				{
					float RemainingTime = FMath::Max(GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle), 0.0f);
					BombText->SetText(FText::FromString(FString::Printf(TEXT("WAVE: %d, Bombs spawn every %.1fs!!"), 
							CurrentWaveIndex + 1, 
							LevelData->LevelWaves[CurrentLevelIndex].WaveDatas[CurrentWaveIndex].BombSpawnInterval)));
				}
				
				if (UFunction* PlayAnimFunc = HUDWidget->FindFunction(FName("PlayAnnounceWaveAnim")))
				{
					HUDWidget->ProcessEvent(PlayAnimFunc, nullptr);
				}
			}
		}
	}
}
