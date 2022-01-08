// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterPlayerController.h"


void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled, bool bIsHeadShot)
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	if (PlayerController && bIsHeadShot)
		PlayerController->ShowHeadshotUI();
}