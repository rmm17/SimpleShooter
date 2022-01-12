// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"
#include "Kismet/GameplayStatics.h"

#define RootName TEXT("Root")
#define MeshName TEXT("Mesh")

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(RootName);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(MeshName);
	Mesh->SetupAttachment(Root);

	SetRootComponent(Root);
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = MaxAmmo;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::PullTrigger()
{
	if (CurrentAmmo > 0)
		CurrentAmmo--;
	else if (EmptyCartridgeSound)
		UGameplayStatics::SpawnSoundAttached(EmptyCartridgeSound, Mesh, TEXT("MuzzleFlashSocket"));

}

void AWeapon::Reload()
{
	CurrentAmmo = MaxAmmo;
}

int32 AWeapon::GetCurrentAmmo()
{
	return CurrentAmmo;
}

int32 AWeapon::GetMaxAmmo()
{
	return MaxAmmo;
}

bool AWeapon::AimTrace(FHitResult& Hit, FVector& ShotDirection)
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

AController* AWeapon::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
		return nullptr;

	return OwnerPawn->GetController();
}

