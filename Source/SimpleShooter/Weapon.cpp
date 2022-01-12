// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

