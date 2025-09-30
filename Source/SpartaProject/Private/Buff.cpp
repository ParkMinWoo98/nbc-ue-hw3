#include "Buff.h"

int32 UBuff::NextId = 0;

UBuff::UBuff()
{
	BuffStackType = EBuffStackType::IgnoreIfExist;
}

void UBuff::Apply_Implementation(ASpartaCharacter* Target)
{
	SetId();
	SetRemainTime(Duration);
}

void UBuff::Tick_Implementation(ASpartaCharacter* Target, float DeltaTime)
{
	RemainTime -= DeltaTime;
}

void UBuff::Remove_Implementation(ASpartaCharacter* Target)
{
}

void UBuff::SetId()
{
	BuffId = NextId++;
	UE_LOG(LogTemp, Warning, TEXT("BuffId: %d ======= %d"), BuffId, NextId);
}

void UBuff::SetRemainTime(float NewRemainTime)
{
	RemainTime = NewRemainTime;
}

void UBuff::AddRemainTime(float AdditionalRemainTime)
{
	RemainTime += AdditionalRemainTime;
}

EBuffStackType UBuff::GetStackType() const
{
	return BuffStackType;
}

int32 UBuff::GetId() const
{
	return BuffId;
}

FName UBuff::GetName() const
{
	return BuffName;
}

float UBuff::GetDuration() const
{
	return Duration;
}

float UBuff::GetRemainTime() const
{
	return RemainTime;
}
