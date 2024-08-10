// https://github.com/Kyrylo-Smyrnov/ShooterGame

#include "Dev/SGDevDamageActor.h"

ASGDevDamageActor::ASGDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(SceneComponent);
}

void ASGDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr,
										DoFullDamage);
}

void ASGDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}
