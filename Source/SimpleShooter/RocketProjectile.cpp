// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

#define StaticMeshName TEXT("Static Mesh")
#define ProjectileMovName TEXT("Projectile Movement")

// Sets default values
ARocketProjectile::ARocketProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(StaticMeshName);
	RootComponent = StaticMeshComp;

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
}

void ARocketProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AShooterCharacter* CharacterHit = Cast<AShooterCharacter>(OtherActor);

	TArray<AActor*> IgnoreActors;

	IgnoreActors.Add(this);
	IgnoreActors.Add(GetOwner());

	UGameplayStatics::ApplyRadialDamage(
		this,
		50.f,
		GetActorLocation(),
		2000.f,
		UDamageType::StaticClass(),
		IgnoreActors,
		this,
		GetOwner()->GetInstigatorController()
	);

	Destroy();
}

