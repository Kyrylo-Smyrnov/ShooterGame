// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/SGBaseCharacter.h"
#include "SGCharacterMovementComponent.generated.h"

UCLASS()
class SHOOTERGAME_API USGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

  public:
	virtual float GetMaxSpeed() const override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = 1.0f, ClampMax = 10.0f));
	float SprintModifier = 1.5;
};