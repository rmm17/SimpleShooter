// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* ShooterController = OwnerComp.GetAIOwner();

	if (!ShooterController)
		return EBTNodeResult::Failed;

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(ShooterController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	Pawn->Shoot();

	return EBTNodeResult::Succeeded;
}