// Fill out your copyright notice in the Description page of Project Settings.


#include "RocketProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
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
	UE_LOG(LogTemp, Warning, TEXT("Rocket hit"));

	AShooterCharacter* CharacterHit = Cast<AShooterCharacter>(OtherActor);



	/*if (CharacterHit)
	{
		FPointDamageEvent DamageEvent = FPointDamageEvent(50.f, Hit, NormalImpulse, nullptr);
		CharacterHit->TakeDamage(50.f, DamageEvent, GetOwner()->GetInstigatorController(), GetOwner());
	}*/

	Destroy();
}

