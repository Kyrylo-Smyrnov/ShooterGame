// https://github.com/Kyrylo-Smyrnov/ShooterGame


#include "Player/SGBaseCharacter.h"

ASGBaseCharacter::ASGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(GetRootComponent());
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
}

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ASGBaseCharacter::MoveForward(float Amount)
{
	AddMovementInput(GetActorForwardVector(), Amount);
}

void ASGBaseCharacter::MoveRight(float Amount)
{
	AddMovementInput(GetActorRightVector(), Amount);
}