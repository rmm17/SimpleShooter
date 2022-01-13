// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Reload.h"
#include "AIController.h"
#include "ShooterCharacter.h"

UBTTask_Reload::UBTTask_Reload()
{
	NodeName = TEXT("Reload");
}

EBTNodeResult::Type UBTTask_Reload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* ShooterController = OwnerComp.GetAIOwner();

	if (!ShooterController)
		return EBTNodeResult::Failed;

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(ShooterController->GetPawn());

	if (!Pawn)
		return EBTNodeResult::Failed;

	Pawn->Reload();

	return EBTNodeResult::Succeeded;
}