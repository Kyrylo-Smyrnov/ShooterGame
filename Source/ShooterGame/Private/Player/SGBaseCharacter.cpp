// https://github.com/Kyrylo-Smyrnov/ShooterGame


#include "Player/SGBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

#include <windows/PxWindowsIntrinsics.h>

ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);

	HealthComponent = CreateDefaultSubobject<USGHealthComponent>("HealthComponent");

	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const auto Health = HealthComponent->GetHealth();
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASGBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASGBaseCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &ASGBaseCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnAround", this, &ASGBaseCharacter::TurnAround);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASGBaseCharacter::Jump);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASGBaseCharacter::OnBeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASGBaseCharacter::OnEndSprint);
}

bool ASGBaseCharacter::IsSprinting() const
{
	return WantToSprint && IsMovingForward && !GetVelocity().IsZero();
}

float ASGBaseCharacter::GetMovementDirection() const
{
	if (!GetVelocity().IsZero())
	{
		const FVector VelocityNormal = GetVelocity().GetSafeNormal();
		const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
		const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
		const float Degrees = FMath::RadiansToDegrees(AngleBetween);

		return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
	}

	return 0.0f;
}

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(HealthTextComponent);
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	if (!Amount == 0)
	{
		IsMovingForward = Amount > 0;
		AddMovementInput(GetActorForwardVector(), Amount);
	}
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	if (!Amount == 0)
	{
		AddMovementInput(GetActorRightVector(), Amount);
	}
}

void ASGBaseCharacter::LookUp(float Amount)
{
	AddControllerPitchInput(Amount);
}

void ASGBaseCharacter::TurnAround(float Amount)
{
	AddControllerYawInput(Amount);
}

void ASGBaseCharacter::OnBeginSprint()
{
	WantToSprint = true;
}

void ASGBaseCharacter::OnEndSprint()
{
	WantToSprint = false;
}