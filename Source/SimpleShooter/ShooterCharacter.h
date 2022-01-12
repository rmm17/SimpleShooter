// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;
class ARocketLauncher;
class AWeapon;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	//BlueprintPure removes the execution pin on the blueprint and implies that we are not making changes to the game state in this function. 
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	UFUNCTION(BlueprintPure)
	bool IsReloading() const;

	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintPure)
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintPure)
	int32 GetMaxAmmo() const;

	void Shoot();

	void ReloadComplete();

private:
	void SetupWeaponList();
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void LookUpRate(float AxisValue);
	void StrafeRight(float AxisValue);
	void LookRight(float AxisValue);
	void LookRightRate(float AxisValue);
	void JumpAction();
	void Reload();
	void SelectWeapon(int32 Index);
	void Zoom();
	void Unzoom();
	void GamepadZoom();
	void CheckIfDead(FDamageEvent const& DamageEvent);

	UPROPERTY(EditAnywhere)
	float RotationRate = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100.f;

	UPROPERTY(VisibleAnywhere)
	float Health = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY(EditDefaultsOnly)
    TSubclassOf<ARocketLauncher> RocketLauncherClass;

	UPROPERTY()
	AWeapon* Weapon;

	TMap<int32, AWeapon*> WeaponList;

	UPROPERTY()
	class USpringArmComponent* SpringArmPtr;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomedTargetArmLength = 150.f;

	UPROPERTY(EditDefaultsOnly, Category = "Camera")
	float ZoomInterpolationSpeed = 10.f;

	UPROPERTY(VisibleAnywhere)
	float OriginalTargetArmLength = 0.f; // used only to store the original target arm length from the SpringArmComponent, for unzooming

	bool bIsZoomPressed = false;

	bool bIsReloading = false;

	FTimerHandle ReloadTimer;
};