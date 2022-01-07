// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Screen Widgets")
	TSubclassOf<class UUserWidget> HUDWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Screen Widgets")
	TSubclassOf<class UUserWidget> WinGameWidgetClass;

	UPROPERTY(EditAnywhere, Category = "Screen Widgets")
	TSubclassOf<class UUserWidget> LostGameWidgetClass;

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	UPROPERTY()
	class UUserWidget* HUDScreen;

	FTimerHandle RestartTimer;
};
