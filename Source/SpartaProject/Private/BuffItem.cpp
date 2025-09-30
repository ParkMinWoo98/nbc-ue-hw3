#include "BuffItem.h"
#include "Buff.h"
#include "SpartaCharacter.h"

ABuffItem::ABuffItem()
{
	ItemType = "BuffItem";
}

void ABuffItem::ActivateItem_Implementation(AActor* Activator)
{
	Super::ActivateItem_Implementation(Activator);

	if (!Activator) return;

	if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
	{
		if (BuffTemplate)
		{
			UBuff* BuffInstance = DuplicateObject<UBuff>(BuffTemplate, this);
			BuffInstance->SetId();
			PlayerCharacter->AddBuff(BuffInstance);
		}
		DestroyItem();
	}
}