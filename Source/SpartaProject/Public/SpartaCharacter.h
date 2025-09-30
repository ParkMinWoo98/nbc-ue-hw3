// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UWidgetComponent;
class UCharacterBuffComponent;
class UCharacterAttribute;
class UBuff;
struct FInputActionValue;

UENUM(BlueprintType, meta = (Bitflags))
enum class ECharacterAilment : uint8
{
	None			= 0			UMETA(DisplayName = "None"),
	Blind			= 1 << 0	UMETA(DisplayName = "Blind"),
	Stunned			= 1 << 1	UMETA(DisplayName = "Stunned"),
};

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;
	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddBuff(UBuff* Buff);

	UFUNCTION(BlueprintCallable, Category = "Ailment")
	void AddAilment(ECharacterAilment InAilment);
	UFUNCTION(BlueprintCallable, Category = "Ailment")
	void RemoveAilment(ECharacterAilment InAilment);
	UFUNCTION(BlueprintCallable, Category = "Ailment")
	bool HasAilment(ECharacterAilment InAilment);
	void ApplyBlind();

protected:
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void StartJump(const FInputActionValue& Value);
	UFUNCTION()
	void StopJump(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);
	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);
	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Buff")
	UCharacterBuffComponent* BuffComp;
	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Buff")
	UCharacterAttribute* AttributeComp;
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> BlindPanelWidgetClass;
	UPROPERTY()
	UUserWidget* BlindPanelWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECharacterAilment"))
	uint8 Ailment;
};
