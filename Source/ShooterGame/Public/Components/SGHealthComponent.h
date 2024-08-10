// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "SGHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SHOOTERGAME_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

  public:
	USGHealthComponent();

	UFUNCTION(BlueprintCallable)
	bool IsDead() const;

	float GetHealth() const;

	FOnDeath OnDeath;
	FOnHealthChanged OnHealthChanged;

  protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = 1.0f, ClampMax = 100.0f), Category = "Health");
	float MaxHealth = 100.0f;

  private:
	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType,
						 class AController* InstigatedBy, AActor* DamageCauser);

	float Health = 0.0f;
};