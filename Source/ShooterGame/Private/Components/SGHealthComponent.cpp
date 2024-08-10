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
	UE_LOG(LogHealthComponent, Display, TEXT("Taken damage: %f"), Damage);

	if(DamageType)
	{
		if(DamageType->IsA<USGFireDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("Damaged by fire."));
		}
		else if(DamageType->IsA<USGIceDamageType>())
		{
			UE_LOG(LogHealthComponent, Display, TEXT("Damaged by ice."));
		}
	}
}
