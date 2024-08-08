// https://github.com/Kyrylo-Smyrnov/ShooterGame


#include "Components/SGHealthComponent.h"

USGHealthComponent::USGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float USGHealthComponent::GetHealth() const
{
	return Health;
}

void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
}