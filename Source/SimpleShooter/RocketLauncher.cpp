// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"
#include "Components/SceneComponent.h"
#include "RocketProjectile.h"

#define SpawnProjectileName TEXT("Spawn Projectile")

#define OUT

// Sets default values
ARocketLauncher::ARocketLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnProjectileComp = CreateDefaultSubobject<USceneComponent>(SpawnProjectileName);
	SpawnProjectileComp->SetupAttachment(Root);
}

bool ARocketLauncher::PullTrigger()
{
	bool bSuccess = Super::PullTrigger();

	if (!bSuccess)
		return false;

	if (!RocketProjectileClass)
		return false;

	FHitResult Hit;
	FVector ShotDirection;
	
	AimTrace(OUT Hit, OUT ShotDirection);

	FRotator SpawnRotation = (Hit.Location - SpawnProjectileComp->GetComponentLocation()).Rotation();

	ARocketProjectile* Projectile = GetWorld()->SpawnActor<ARocketProjectile>(
		RocketProjectileClass,
		SpawnProjectileComp->GetComponentLocation(),
		SpawnRotation
	);
	
	if (Projectile)
		Projectile->SetOwner(GetOwner());

	return true;
}