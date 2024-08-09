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

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
}

void USGHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
										 class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= Damage;
}
