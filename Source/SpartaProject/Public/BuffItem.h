#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "BuffItem.generated.h"

class UBuff;

UCLASS()
class SPARTAPROJECT_API ABuffItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	ABuffItem();

	void ActivateItem_Implementation(AActor* Activator);

protected:
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category = "Buff")
	UBuff* BuffTemplate;
};
