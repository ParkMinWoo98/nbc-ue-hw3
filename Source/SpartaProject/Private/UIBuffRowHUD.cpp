#include "UIBuffRowHUD.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "UIBuffInfoHUD.h"
#include "Buff.h"

FName UUIBuffRowHUD::GetName() const
{
	return BuffName;
}

void UUIBuffRowHUD::SetBuffName(FName NewBuffName)
{
	BuffName = NewBuffName;
	if (TextBuffName)
	{
		TextBuffName->SetText(FText::FromName(BuffName));
	}
}

void UUIBuffRowHUD::AddBuff(UBuff* Buff)
{
	if (!Buff || Buff->GetName() != BuffName) return;

	UUIBuffInfoHUD* BuffInfo = CreateWidget<UUIBuffInfoHUD>(GetWorld(), BuffInfoClass);
	if (!BuffInfo) return;

	BuffInfo->SetData(Buff);
	BuffInfo->OnBuffInfoRemoved.AddDynamic(this, &UUIBuffRowHUD::CheckBuffInfos);
	BuffInfoParent->AddChild(BuffInfo);
}

void UUIBuffRowHUD::CheckBuffInfos()
{
	if (BuffInfoParent->GetChildrenCount() <= 1)
	{
		RemoveFromParent();
		OnBuffRowRemoved.Broadcast(BuffName);
	}
}
