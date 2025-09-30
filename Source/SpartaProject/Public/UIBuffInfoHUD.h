#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBuffInfoHUD.generated.h"

class UBuff;
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuffInfoRemoved);

UCLASS()
class SPARTAPROJECT_API UUIBuffInfoHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION()
	void SetData(UBuff* Buff);
	UFUNCTION()
	void UpdateData();

	UPROPERTY(BlueprintAssignable, Category = "BuffInfo")
	FOnBuffInfoRemoved OnBuffInfoRemoved;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextMainValue;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextSubValue;

	UPROPERTY()
	UBuff* BuffData;
};
