#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "CoinItem.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);

	SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
	SpawningBox->SetupAttachment(Scene);
	ItemDataTable = nullptr;
}

AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	if (!ItemClass) return nullptr;
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointInVolume(),
		FRotator::ZeroRotator);
	return SpawnedActor;
}

AActor* ASpawnVolume::SpawnRandomItem(TSubclassOf<AActor> ItemClass)
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem(ItemClass))
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}
	return nullptr;
}

FItemSpawnRow* ASpawnVolume::GetRandomItem(TSubclassOf<AActor> ItemClass) const
{
	if (!ItemDataTable) return nullptr;

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ItemSpawnContext"));
	ItemDataTable->GetAllRows(ContextString, AllRows);

	if (ItemClass == nullptr)
		return GetRandomItem(AllRows);

	TArray<FItemSpawnRow*> SelectedItemRows;
	for (FItemSpawnRow* Row : AllRows)
	{
		if (Row->ItemClass.Get()->IsChildOf(ItemClass))
		{
			SelectedItemRows.Add(Row);
		}
	}
	return GetRandomItem(SelectedItemRows);
}

FItemSpawnRow* ASpawnVolume::GetRandomItem(const TArray<FItemSpawnRow*> ItemSpawnRows) const
{
	if (ItemSpawnRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : ItemSpawnRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandValue = FMath::FRandRange(0.0f, TotalChance);
	float AccumulateChance = 0.0f;
	for (FItemSpawnRow* Row : ItemSpawnRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandValue <= AccumulateChance)
		{
			return Row;
		}
	}

	return nullptr;
}

FVector ASpawnVolume::GetRandomPointInVolume() const
{
	FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
	FVector BoxOrigin = SpawningBox->GetComponentLocation();
	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z));
}
