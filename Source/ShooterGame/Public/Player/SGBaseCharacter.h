// https://github.com/Kyrylo-Smyrnov/ShooterGame

#pragma once

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SGCharacterMovementComponent.h"
#include "Components/SGHealthComponent.h"
#include "Components/TextRenderComponent.h"
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

	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprinting() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	float GetMovementDirection() const;

  protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USGHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* DeathAnimMontage;

  private:
	void MoveForward(float Amount);
	void MoveRight(float Amount);

	void LookUp(float Amount);
	void TurnAround(float Amount);

	void OnBeginSprint();
	void OnEndSprint();

	void OnDeath();
	void OnHealthChanged(float Health);

	bool IsMovingForward = false;
	bool WantToSprint = false;
};