#include "DangerAreaComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

UDangerAreaComponent::UDangerAreaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UDangerAreaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!Decal) return;

	DecalTimer = FMath::Min(DecalDuration, DecalTimer + DeltaTime);
	float Progress = DecalDuration > 0.0f ? DecalTimer / DecalDuration : 1.0f;
	switch (Type)
	{
		case DangerAreaEffectType::None:
			break;
		case DangerAreaEffectType::Fill:
			Decal->SetRelativeScale3D(FVector(1.0f, Progress, Progress));
			break;
		case DangerAreaEffectType::FadeIn:
			MaterialAreaInstance->SetScalarParameterValue(TEXT("OpacityMultiplier"), Progress);
			break;
		default:
			break;
	}

	if (Decal && bEndAfterDuration && DecalTimer >= DecalDuration)
	{
		Decal->DestroyComponent();
		Decal = nullptr;
	}
}

void UDangerAreaComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Decal)
		Decal->DestroyComponent();
	Super::EndPlay(EndPlayReason);
}

void UDangerAreaComponent::Spawn(const FVector& Size, const FVector& Location, const FRotator& Rotation, float Duration, DangerAreaEffectType InType, bool bNewEndAfterDuration)
{
	SetComponentTickEnabled(true);
	DecalTimer = 0.0f;
	Type = InType;
	DecalSize = Size;
	DecalDuration = Duration;
	bEndAfterDuration = bNewEndAfterDuration;
	MaterialAreaInstance = UMaterialInstanceDynamic::Create(MaterialArea, this);
	Decal = UGameplayStatics::SpawnDecalAtLocation(
		GetWorld(),
		MaterialAreaInstance,
		Size,
		Location,
		Rotation,
		0.0f);
}

