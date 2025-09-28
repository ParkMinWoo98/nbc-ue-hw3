#include "BigCoinItem.h"

ABigCoinItem::ABigCoinItem()
{
	PointValue = 50;
	ItemType = "BigCoin";
}

void ABigCoinItem::ActivateItem_Implementation(AActor* Activator)
{
	ACoinItem::ActivateItem_Implementation(Activator);
}