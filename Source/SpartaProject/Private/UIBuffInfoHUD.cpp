#include "UIBuffInfoHUD.h"
#include "Buff.h"
#include "Components/TextBlock.h"
#include "MoveSpeedBuff.h"

void UUIBuffInfoHUD::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	UpdateData();
}

void UUIBuffInfoHUD::SetData(UBuff* Buff)
{
	BuffData = Buff;
	if (TextSubValue)
	{
		if (UMoveSpeedBuff* MoveSpeedBuff = Cast<UMoveSpeedBuff>(BuffData))
		{
			TextSubValue->SetText(FText::FromString(FString::Printf(TEXT("%.2f"), MoveSpeedBuff->GetSpeedMultiplier())));
			TextSubValue->SetVisibility(ESlateVisibility::Visible);
		}
		else
		{
			TextSubValue->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	UpdateData();
}

void UUIBuffInfoHUD::UpdateData()
{
	if (!IsValid(BuffData) || BuffData->GetRemainTime() <= 0.0f)
	{
		RemoveFromParent();
		OnBuffInfoRemoved.Broadcast();
		return;
	}

	if (TextMainValue)
	{
		TextMainValue->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), BuffData->GetRemainTime())));
	}
}
