// https://github.com/Kyrylo-Smyrnov/ShooterGame

#include "SGGameModeBase.h"

ASGGameModeBase::ASGGameModeBase()
{
	DefaultPawnClass = ASGBaseCharacter::StaticClass();
	PlayerControllerClass = ASGPlayerController::StaticClass();
}
