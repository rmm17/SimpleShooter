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
	if (!MuzzleFlash)
		return;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
		return;

	AController* OwnerController = OwnerPawn->GetController();
	if (!OwnerController)
		return;

	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	FVector StartLocation;
	FRotator StartRotation;
	OwnerController->GetPlayerViewPoint(OUT StartLocation, OUT StartRotation);

	FVector End = StartLocation + StartRotation.Vector() * MaxRange;

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(OUT Hit, StartLocation, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess) {
		FVector ShotDirection = -StartRotation.Vector();

		if (ImpactParticles)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticles, Hit.Location, ShotDirection.Rotation());
		
		if (auto ActorHit = Hit.GetActor())
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			ActorHit->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
}

