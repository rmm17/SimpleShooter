// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "ShooterCharacter.h"

#define StaticMeshName TEXT("Static Mesh")
#define ProjectileMovName TEXT("Projectile Movement")
#define SmokeTrailName TEXT("Smoke Trail")

// Sets default values
ARocketProjectile::ARocketProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshName);
	RootComponent = StaticMeshComp;

	ParticleSystemComp = CreateDefaultSubobject<UParticleSystemComponent>(SmokeTrailName);
	RootComponent->SetupAttachment(ParticleSystemComp);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(ProjectileMovName);


	if (!ProjectileMovementComp)
		return;

	ProjectileMovementComp->InitialSpeed = 3000.f;
	ProjectileMovementComp->MaxSpeed = 3000.f;
}

// Called when the game starts or when spawned
void ARocketProjectile::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComp->OnComponentHit.AddDynamic(this, &ARocketProjectile::OnHit);

	if (RocketLaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, RocketLaunchSound, GetActorLocation());
}

void ARocketProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AShooterCharacter* CharacterHit = Cast<AShooterCharacter>(OtherActor);

	TArray<AActor*> IgnoreActors;

	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	FVector ActorLocation = GetActorLocation();

	UGameplayStatics::ApplyRadialDamage(
		this,
		50.f,
		ActorLocation,
		2000.f,
		UDamageType::StaticClass(),
		IgnoreActors,
		this,
		GetOwner()->GetInstigatorController()
	);

	Destroy();

	if (HitParticles)
	{
		FVector ParticlesScale(0.25f);
		UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, ActorLocation, GetActorRotation(), ParticlesScale);
	}

	if (RocketExplosionSound)
		UGameplayStatics::PlaySoundAtLocation(this, RocketExplosionSound, ActorLocation);
}

