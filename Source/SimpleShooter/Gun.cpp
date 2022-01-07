// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#define RootName TEXT("Root")
#define MeshName TEXT("Mesh")

#define OUT

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(RootName);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(MeshName);
	Mesh->SetupAttachment(Root);

	SetRootComponent(Root);
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

	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
		return;

	if (MuzzleFlash)
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	if (GunTrace(OUT Hit, OUT ShotDirection)) {
		if (ImpactParticles)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, Hit.Location, ShotDirection.Rotation());
		
		if (auto ActorHit = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	FVector StartLocation;
	FRotator StartRotation;

	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
		return false;

	OwnerController->GetPlayerViewPoint(OUT StartLocation, OUT StartRotation);
	ShotDirection = -StartRotation.Vector();

	FVector End = StartLocation + StartRotation.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(OUT Hit, StartLocation, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
		return nullptr;

	return OwnerPawn->GetController();
}

