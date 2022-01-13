// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "RocketLauncher.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ARocketLauncher : public AWeapon
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARocketLauncher();

	virtual bool PullTrigger() override;

private:
	void RocketTrace();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USceneComponent* SpawnProjectileComp;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class ARocketProjectile> RocketProjectileClass;
};
