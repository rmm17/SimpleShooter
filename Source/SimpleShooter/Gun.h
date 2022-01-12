// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AWeapon
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	virtual void PullTrigger() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* MuzzleFlash;
	
	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* ImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class TSubclassOf<class UDamageType> HeadShotDamageTypeClass;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RegularDamage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HeadShotDamage = 100.f;

	void GenerateMuzzleEffects() const;
	void GenerateImpactEffects(FVector ImpactLocation, FRotator ImpactRotation) const;
};
