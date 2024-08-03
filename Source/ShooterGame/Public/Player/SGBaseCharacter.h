// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SGCharacterMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "SGBaseCharacter.generated.h"

UCLASS()
class SHOOTERGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGBaseCharacter(const FObjectInitializer& ObjInit);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Movement")
	bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category="Movement")
	float GetMovementDirection() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnBeginSprint();
	void OnEndSprint();

	bool IsMovingForward = false;
	bool WantToSprint = false;
};