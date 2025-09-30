#include "CharacterAttribute.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SpartaGameState.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

UCharacterAttribute::UCharacterAttribute()
{
	PrimaryComponentTick.bCanEverTick = false;

	NormalSpeed = 600.0f;
	SprintSpeedMultiplier = 2.0f;

	MaxHealth = 100.0f;
	Health = MaxHealth;

	bIsSprinting = false;
	bReverseControl = false;
}

void UCharacterAttribute::BeginPlay()
{
	Super::BeginPlay();

	UpdateOverheadHp();
}

//void UCharacterAttribute::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//}

float UCharacterAttribute::GetHealth() const
{
	return Health;
}

float UCharacterAttribute::GetMaxHealth() const
{
	return MaxHealth;
}

void UCharacterAttribute::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	UpdateOverheadHp();
	UE_LOG(LogTemp, Warning, TEXT("Health increased to: %f"), Health);
}

float UCharacterAttribute::ApplyDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	UpdateOverheadHp();
	UE_LOG(LogTemp, Warning, TEXT("Health decreased to: %f"), Health);
	if (Health <= 0.0f)
	{
		OnDeath();
	}
	return Damage;
}

void UCharacterAttribute::OnDeath()
{
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		SpartaGameState->OnGameOver();
	}
}

void UCharacterAttribute::UpdateOverheadHp()
{
	if (UWidgetComponent* OverheadWidget = GetOwner()->FindComponentByClass<UWidgetComponent>())
	{
		UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
		if (!OverheadWidgetInstance) return;

		if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverheadHp"))))
		{
			HPText->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Health, MaxHealth)));
		}
	}
}

void UCharacterAttribute::AddSpeedModifier(int32 BuffId, float Modifier)
{
	SpeedModifiers.Add(BuffId, Modifier);
}

void UCharacterAttribute::RemoveSpeedModifier(int32 BuffId)
{
	SpeedModifiers.Remove(BuffId);
}

void UCharacterAttribute::RecalculateSpeed()
{
	float BuffSpeed = 1.0f;
	for (const auto& p : SpeedModifiers)
	{
		BuffSpeed *= p.Value;
	}
	float Speed = NormalSpeed * BuffSpeed;
	if (bIsSprinting)
	{
		Speed *= SprintSpeedMultiplier;
	}

	if (UCharacterMovementComponent* Movement = GetOwner()->FindComponentByClass<UCharacterMovementComponent>())
	{
		Movement->MaxWalkSpeed = Speed;
	}

	/*GEngine->AddOnScreenDebugMessage(
		-1,
		6.0f,
		FColor::Green,
		FString::Printf(TEXT("MaxSpeed: %f"), Speed));*/
}

void UCharacterAttribute::Sprint(bool bSprinting)
{
	if (bIsSprinting == bSprinting) return;
	bIsSprinting = bSprinting;
	RecalculateSpeed();
}

bool UCharacterAttribute::GetReverseControl() const
{
	return bReverseControl;
}

void UCharacterAttribute::SetReverseControl(bool bReverse)
{
	bReverseControl = bReverse;
}

