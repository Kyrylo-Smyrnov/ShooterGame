// https://github.com/Kyrylo-Smyrnov/ShooterGame


#include "Player/SGBaseCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	IsMovingForward = Amount > 0;
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
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