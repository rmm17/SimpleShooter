// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "TimerManager.h"

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		if (WinGameWidgetClass)
		{
			UUserWidget* WinScreen = CreateWidget(this, WinGameWidgetClass);

			if (WinScreen)
				WinScreen->AddToViewport();
		}
	}
	else if (LostGameWidgetClass)
	{
		UUserWidget* LoseScreen = CreateWidget(this, LostGameWidgetClass);

		if (LoseScreen)
			LoseScreen->AddToViewport();
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &AShooterPlayerController::RestartLevel, RestartDelay);
}