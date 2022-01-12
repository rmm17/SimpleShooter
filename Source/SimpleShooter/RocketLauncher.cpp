// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketLauncher.h"
#include "Components/SceneComponent.h"

#define SpawnProjectileName TEXT("Spawn Projectile")

// Sets default values
ARocketLauncher::ARocketLauncher()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnProjectileComp = CreateDefaultSubobject<USceneComponent>(SpawnProjectileName);
	SpawnProjectileComp->SetupAttachment(Root);
}