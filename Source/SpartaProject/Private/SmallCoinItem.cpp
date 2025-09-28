#include "SmallCoinItem.h"

ASmallCoinItem::ASmallCoinItem()
{
	PointValue = 10;
	ItemType = "SmallCoin";
}

void ASmallCoinItem::ActivateItem_Implementation(AActor* Activator)
{
	ACoinItem::ActivateItem_Implementation(Activator);
}