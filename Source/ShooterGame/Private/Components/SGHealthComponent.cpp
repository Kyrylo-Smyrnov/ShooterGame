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
	return FMath::IsNearlyZero(Health);
}

void USGHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	SetHealth(MaxHealth);

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USGHealthComponent::OnTakeAnyDamage);
}

void USGHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
										 class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || IsDead() || !GetWorld())
		return;

	GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);

	SetHealth(Health - Damage);

	if (IsDead())
		OnDeath.Broadcast();
	else if (IsAutoHealEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, this, &USGHealthComponent::AutoHeal, AutoHealRate,
											   true, AutoHealDelay);
	}
}

void USGHealthComponent::SetHealth(float NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
	OnHealthChanged.Broadcast(Health);
}

void USGHealthComponent::AutoHeal()
{
	SetHealth(Health + AutoHealAmount);

	if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
		GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);
}
