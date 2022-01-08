// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "DeathmatchGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API ADeathmatchGameModeBase : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* PawnKilled, bool bIsHeadShot) override;

private:
	void CheckIfAllEnemiesDead();
	void EndGame(bool bIsGameWon);
};
