// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchGameModeBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

void ADeathmatchGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	if (!PawnKilled)
		return;

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (PlayerController && PlayerPawn == PawnKilled)
		PlayerController->GameHasEnded(nullptr, false);
}
