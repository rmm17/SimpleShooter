// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

#define BBPlayerLocationName TEXT("PlayerLocation")
#define BBStartLocationName TEXT("StartLocation")
#define BBLastKnownLocationName TEXT("LastKnownPlayerLocation")

void AShooterAIController::BeginPlay() 
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);

	if (AIBehavior)
	{
		RunBehaviorTree(AIBehavior);

		if (Blackboard && GetPawn())
			Blackboard->SetValueAsVector(BBStartLocationName, GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

	if (ControlledCharacter)
		return ControlledCharacter->IsDead();

	return true;
}