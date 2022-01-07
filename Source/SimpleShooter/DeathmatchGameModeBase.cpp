// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchGameModeBase.h"
#include "EngineUtils.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAIController.h"

void ADeathmatchGameModeBase::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);

	if (!PawnKilled)
		return;

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (PlayerPawn == PawnKilled)
		EndGame(false);
	else CheckIfAllEnemiesDead();
}

void ADeathmatchGameModeBase::CheckIfAllEnemiesDead()
{
	bool bAllEnemiesDead = true;
	for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
	{
		if (!Controller->IsDead())
		{
			bAllEnemiesDead = false;
			break;
		}
	}

	if (bAllEnemiesDead)
		EndGame(true);
}

void ADeathmatchGameModeBase::EndGame(bool bIsGameWon)
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsGameWon; // (bIsPlayerController && bIsGameWon) || (!bIsPlayerController && !bIsGameWon);

		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
