// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MoveToWhileNotSeen.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

UBTTask_MoveToWhileNotSeen::UBTTask_MoveToWhileNotSeen()
{
	NodeName = TEXT("Move To While Player Not Seen");
}

void UBTTask_MoveToWhileNotSeen::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// TODO: Code needs revision, not working as intended
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* ShooterController = OwnerComp.GetAIOwner();
	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (!ShooterController || !PlayerPawn)
		return;

	if (ShooterController->LineOfSightTo(PlayerPawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); 
	}
}