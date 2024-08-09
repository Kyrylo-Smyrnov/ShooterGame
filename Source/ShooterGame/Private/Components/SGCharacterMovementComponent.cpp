// https://github.com/Kyrylo-Smyrnov/ShooterGame

#include "Components/SGCharacterMovementComponent.h"

float USGCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ASGBaseCharacter* Player = Cast<ASGBaseCharacter>(GetPawnOwner());

	return Player && Player->IsSprinting() ? MaxSpeed * SprintModifier : MaxSpeed;
}