#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UIBuffRowHUD.generated.h"

class UTextBlock;
class UHorizontalBox;
class UUIBuffInfoHUD;
class UBuff;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffRowRemoved, FName, BuffName);

UCLASS()
class SPARTAPROJECT_API UUIBuffRowHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	FName GetName() const;
	UFUNCTION()
	void SetBuffName(FName NewBuffName);
	UFUNCTION()
	void AddBuff(UBuff* Buff);
	UFUNCTION()
	void CheckBuffInfos();

	UPROPERTY(BlueprintAssignable, Category = "BuffInfo")
	FOnBuffRowRemoved OnBuffRowRemoved;

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextBuffName;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* BuffInfoParent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUIBuffInfoHUD> BuffInfoClass;

	UPROPERTY()
	FName BuffName;
};
