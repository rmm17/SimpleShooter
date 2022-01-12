// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GunDamageType.h"

#define HeadBoneName TEXT("head")

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	Super::PullTrigger();

	if (GetCurrentAmmo() <= 0)
	{
		return;
	}

	FHitResult Hit;
	FVector ShotDirection;

	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
		return;

	GenerateMuzzleEffects();

	if (AimTrace(OUT Hit, OUT ShotDirection)) {
		GenerateImpactEffects(Hit.Location, ShotDirection.Rotation());

		if (auto ActorHit = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent;

			float DamageTaken = 0.f;

			if (Hit.BoneName.IsEqual(FName(HeadBoneName)))
			{
				DamageTaken = HeadShotDamage;
				DamageEvent = FPointDamageEvent(DamageTaken, Hit, ShotDirection, HeadShotDamageTypeClass);
			}
			else
			{
				DamageTaken = RegularDamage;
				DamageEvent = FPointDamageEvent(DamageTaken, Hit, ShotDirection, nullptr);
			}
			
			ActorHit->TakeDamage(DamageTaken, DamageEvent, OwnerController, this);
		}
	}
}

void AGun::GenerateMuzzleEffects() const
{
	if (MuzzleFlash)
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	if (MuzzleSound)
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
}

void AGun::GenerateImpactEffects(FVector ImpactLocation, FRotator ImpactRotation) const
{
	if (ImpactParticles)
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, ImpactLocation, ImpactRotation);

	if (ImpactSound)
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, ImpactLocation);
}

