// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SIMPLESHOOTER_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

	virtual void PullTrigger();
	void Reload();
	int32 GetMaxAmmo();
	int32 GetCurrentAmmo();
	float GetReloadTime();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool AimTrace(FHitResult& Hit, FVector& ShotDirection);
	class AController* GetOwnerController() const;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* Mesh;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* EmptyCartridgeSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ReloadSound;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	int32 MaxAmmo = 32;

	UPROPERTY(VisibleAnywhere, Category = "Combat")
	int32 CurrentAmmo;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float ReloadTime = 1.f;

};
