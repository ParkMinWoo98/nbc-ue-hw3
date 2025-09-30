#include "UIHUD.h"
#include "Buff.h"
#include "UIBuffRowHUD.h"
#include "Components/VerticalBox.h"

void UUIHUD::AddBuff(UBuff* Buff)
{
	FName BuffName = Buff->GetName();
	if (BuffRowMap.Find(BuffName) == nullptr)
	{
		UUIBuffRowHUD* BuffRow = CreateWidget<UUIBuffRowHUD>(GetWorld(), BuffRowClass);
		BuffRow->SetBuffName(BuffName);
		BuffRow->OnBuffRowRemoved.AddDynamic(this, &UUIHUD::CheckBuffRows);
		BuffParent->AddChild(BuffRow);
		BuffRowMap.Add(BuffName, BuffRow);
	}
	BuffRowMap[BuffName]->AddBuff(Buff);
}

void UUIHUD::CheckBuffRows(FName BuffName)
{
	if (BuffRowMap.Find(BuffName))
		BuffRowMap.Remove(BuffName);
}
