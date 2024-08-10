// https://github.com/Kyrylo-Smyrnov/ShooterGame

#include "Components/SGHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

USGHealthComponent::USGHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float USGHealthComponent::GetHealth() const
{
	return Health;
}

bool USGHealthComponent::IsDead() const
{
	return Health <= 0.0f;
}

void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	OnHealthChanged.Broadcast(Health);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
}

void USGHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
										 class AController* InstigatedBy, AActor* DamageCauser)
{
	if(Damage <= 0.0f || IsDead())
		return;
	
	Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
	
	if(IsDead())
		OnDeath.Broadcast();
}
