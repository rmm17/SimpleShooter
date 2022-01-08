// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Gun.h"
#include "GunDamageType.h"
#include "SimpleShooterGameModeBase.h"

#define MoveForwardBinding TEXT("MoveForward")
#define LookUpBinding TEXT("LookUp")
#define LookUpRateBinding TEXT("LookUpRate")
#define StrafeRightBinding TEXT("StrafeRight")
#define LookRightBinding TEXT("LookRight")
#define LookRightRateBinding TEXT("LookRightRate")
#define JumpBinding TEXT("Jump")
#define ShootBinding TEXT("Shoot")
#define ZoomBinding TEXT("Zoom")
#define GamepadZoomBinding TEXT("GamepadZoom")

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
	
	if (Gun)
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, WeaponSocketName);
		Gun->SetOwner(this);
	}

	SpringArmPtr = FindComponentByClass<USpringArmComponent>();
	if (SpringArmPtr)
		OriginalTargetArmLength = SpringArmPtr->TargetArmLength;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (SpringArmPtr) {
		if (bIsZoomPressed)
			SpringArmPtr->TargetArmLength = FMath::FInterpTo(SpringArmPtr->TargetArmLength, ZoomedTargetArmLength, DeltaTime, ZoomInterpolationSpeed);
		else SpringArmPtr->TargetArmLength = FMath::FInterpTo(SpringArmPtr->TargetArmLength, OriginalTargetArmLength, DeltaTime, ZoomInterpolationSpeed);
	}
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
	
	PlayerInputComponent->BindAction(ZoomBinding, EInputEvent::IE_Pressed, this, &AShooterCharacter::Zoom);
	PlayerInputComponent->BindAction(ZoomBinding, EInputEvent::IE_Released, this, &AShooterCharacter::Unzoom);

	PlayerInputComponent->BindAction(GamepadZoomBinding, EInputEvent::IE_Pressed, this, &AShooterCharacter::GamepadZoom);
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

void AShooterCharacter::Shoot()
{
	if (!Gun)
		return;

	Gun->PullTrigger();
}

void AShooterCharacter::Zoom()
{
	bIsZoomPressed = true;
}

void AShooterCharacter::Unzoom()
{
	bIsZoomPressed = false;
}

void AShooterCharacter::GamepadZoom()
{
	bIsZoomPressed = !bIsZoomPressed;
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0;
}

float AShooterCharacter::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	UE_LOG(LogTemp, Warning, TEXT("Damage to apply: %f"), DamageToApply);

	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;

	CheckIfDead(DamageEvent);

	return DamageToApply;
}

void AShooterCharacter::CheckIfDead(FDamageEvent const& DamageEvent)
{
	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		UGunDamageType* GunDamageType = Cast<UGunDamageType>(DamageEvent.DamageTypeClass.GetDefaultObject());

		if (GameMode)
			GameMode->PawnKilled(this, GunDamageType ? true : false);

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}
