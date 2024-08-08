// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USGHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGHealthComponent();

	float GetHealth() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(ClampMin = 1.0f, ClampMax = 100.0f), Category="Health");
	float MaxHealth = 100.0f;

private:
	float Health = 0.0f;
};