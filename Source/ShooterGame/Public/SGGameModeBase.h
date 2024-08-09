// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/SGBaseCharacter.h"
#include "Player/SGPlayerController.h"
#include "SGGameModeBase.generated.h"

UCLASS()
class SHOOTERGAME_API ASGGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

  public:
	ASGGameModeBase();
};