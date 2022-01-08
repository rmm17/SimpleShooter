// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USkeletalMeshComponent* Mesh;

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
	float MaxRange = 3000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float RegularDamage = 20.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float HeadShotDamage = 100.f;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);
	void GenerateMuzzleEffects() const;
	void GenerateImpactEffects(FVector ImpactLocation, FRotator ImpactRotation) const;
	class AController* GetOwnerController() const;
};
