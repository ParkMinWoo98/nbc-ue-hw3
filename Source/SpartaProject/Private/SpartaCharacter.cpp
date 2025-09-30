#include "SpartaCharacter.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterBuffComponent.h"
#include "Components/WidgetComponent.h"
#include "CharacterAttribute.h"

ASpartaCharacter::ASpartaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);
	
	BuffComp = CreateDefaultSubobject<UCharacterBuffComponent>(TEXT("CharacterBuff"));
	AttributeComp = CreateDefaultSubobject<UCharacterAttribute>(TEXT("CharacterAttribute"));

	Ailment = static_cast<uint8>(ECharacterAilment::None);
}

void ASpartaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (BlindPanelWidgetClass)
	{
		BlindPanelWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), BlindPanelWidgetClass);
		if (BlindPanelWidgetInstance)
		{
			BlindPanelWidgetInstance->AddToViewport(0);
			BlindPanelWidgetInstance->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ASpartaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Move);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartJump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopJump);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::Look);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ASpartaCharacter::StartSprint);
		EnhancedInput->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASpartaCharacter::StopSprint);
	}
}

float ASpartaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	return AttributeComp ? AttributeComp->ApplyDamage(ActualDamage) : 0.0f;
}

void ASpartaCharacter::AddHealth(float Amount)
{
	if (AttributeComp)
	{
		AttributeComp->AddHealth(Amount);
	}
}

void ASpartaCharacter::AddBuff(UBuff* Buff)
{
	if (BuffComp)
	{
		BuffComp->AddBuff(Buff);
	}
}

void ASpartaCharacter::AddAilment(ECharacterAilment InAilment)
{
	Ailment |= static_cast<uint8>(InAilment);
	ApplyBlind();
}

void ASpartaCharacter::RemoveAilment(ECharacterAilment InAilment)
{
	Ailment &= ~static_cast<uint8>(InAilment);
	ApplyBlind();
}

bool ASpartaCharacter::HasAilment(ECharacterAilment InAilment)
{
	return (Ailment & static_cast<uint8>(InAilment)) != 0;
}

void ASpartaCharacter::ApplyBlind()
{
	if (BlindPanelWidgetInstance)
	{
		BlindPanelWidgetInstance->SetVisibility(HasAilment(ECharacterAilment::Blind) ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
	}
}

void ASpartaCharacter::Move(const FInputActionValue& Value)
{
	if (!Controller) return;

	bool bReverseControl = AttributeComp ? AttributeComp->GetReverseControl() : false;
	const FVector2D MoveInput = Value.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), bReverseControl ? -MoveInput.X : MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), bReverseControl ? -MoveInput.Y : MoveInput.Y);
	}
}

void ASpartaCharacter::StartJump(const FInputActionValue& Value)
{
	if (Value.Get<bool>())
	{
		Jump();
	}
}

void ASpartaCharacter::StopJump(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		StopJumping();
	}
}

void ASpartaCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookInput = Value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void ASpartaCharacter::StartSprint(const FInputActionValue& Value)
{
	AttributeComp->Sprint(true);
}

void ASpartaCharacter::StopSprint(const FInputActionValue& Value)
{
	AttributeComp->Sprint(false);
}
