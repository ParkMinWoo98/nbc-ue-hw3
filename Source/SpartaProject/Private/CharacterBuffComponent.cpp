#include "CharacterBuffComponent.h"
#include "Buff.h"
#include "SpartaCharacter.h"

UCharacterBuffComponent::UCharacterBuffComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCharacterBuffComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCharacterBuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(GetOwner());
	if (!SpartaCharacter) return;

	for (int32 i = Buffs.Num() - 1; i >= 0; i--)
	{
		Buffs[i]->Tick_Implementation(SpartaCharacter, DeltaTime);
		if (Buffs[i]->GetRemainTime() <= 0.0f)
		{
			Buffs[i]->Remove(SpartaCharacter);
			Buffs.RemoveAt(i);
		}
	}
}

void UCharacterBuffComponent::AddBuff(UBuff* Buff)
{
	ASpartaCharacter* SpartaCharacter = Cast<ASpartaCharacter>(GetOwner());
	if (!SpartaCharacter) return;
	
	switch (Buff->GetStackType())
	{
		case EBuffStackType::IgnoreIfExist:
			if (UBuff* BuffExist = FindBuffOfClass(Buff->GetClass())) return;
			break;
		case EBuffStackType::RefreshDuration:
			if (UBuff* BuffExist = FindBuffOfClass(Buff->GetClass()))
			{
				BuffExist->SetRemainTime(Buff->GetDuration());
				return;
			}
			break;
		case EBuffStackType::AddDuration:
			if (UBuff* BuffExist = FindBuffOfClass(Buff->GetClass()))
			{
				BuffExist->AddRemainTime(Buff->GetDuration());
				return;
			}
			break;
		case EBuffStackType::StackMultiple:
			break;
		default:
			return;
	}

	Buff->Apply(SpartaCharacter);
	Buffs.Add(Buff);
	OnBuffAdded.Broadcast(Buff);
}

UBuff* UCharacterBuffComponent::FindBuffOfClass(TSubclassOf<UBuff> BuffClass) const
{
	for (UBuff* Buff : Buffs)
	{
		if (Buff && Buff->GetClass() == BuffClass)
		{
			return Buff;
		}
	}
	return nullptr;
}
