// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_WaitIfNotSeen.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTTask_WaitIfNotSeen::UBTTask_WaitIfNotSeen()
{
	NodeName = TEXT("Wait If Player Not Seen");
}

void UBTTask_WaitIfNotSeen::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* ShooterController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!ShooterController || !PlayerPawn)
		return;

	if (ShooterController->LineOfSightTo(PlayerPawn))
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}