#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIHUD.generated.h"

class UBuff;
class UVerticalBox;
class UUIBuffRowHUD;

UCLASS(BlueprintType, Blueprintable)
class SPARTAPROJECT_API UUIHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void AddBuff(UBuff* Buff);
	UFUNCTION()
	void CheckBuffRows(FName BuffName);

protected:
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* BuffParent;
	UPROPERTY()
	TMap<FName, UUIBuffRowHUD*> BuffRowMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUIBuffRowHUD> BuffRowClass;
};
