// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"

#define MoveForwardBinding TEXT("MoveForward")
#define LookUpBinding TEXT("LookUp")
#define LookUpRateBinding TEXT("LookUpRate")
#define StrafeRightBinding TEXT("StrafeRight")
#define LookRightBinding TEXT("LookRight")
#define LookRightRateBinding TEXT("LookRightRate")
#define JumpBinding TEXT("Jump")
#define ShootBinding TEXT("Shoot")

#define WeaponSocketName TEXT("WeaponSocket")

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
	Gun->SetOwner(this);
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForwardBinding, this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(LookUpBinding, this, &AShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(LookUpRateBinding, this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(StrafeRightBinding, this, &AShooterCharacter::StrafeRight);
	PlayerInputComponent->BindAxis(LookRightBinding, this, &AShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(LookRightRateBinding, this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(JumpBinding, EInputEvent::IE_Pressed, this, &AShooterCharacter::JumpAction);
	PlayerInputComponent->BindAction(ShootBinding, EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
}

bool AShooterCharacter::isDead() const
{
	return Health <= 0;
}

void AShooterCharacter::Shoot()
{
	if (!Gun)
		return;

	Gun->PullTrigger();
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::StrafeRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::JumpAction()
{
	Jump();
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);

	return DamageToApply;
}
