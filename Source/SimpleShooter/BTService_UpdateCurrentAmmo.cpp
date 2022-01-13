// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_UpdateCurrentAmmo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

UBTService_UpdateCurrentAmmo::UBTService_UpdateCurrentAmmo()
{
	NodeName = TEXT("Update Current Ammo");
}

void UBTService_UpdateCurrentAmmo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* ShooterController = OwnerComp.GetAIOwner();

	if (!ShooterController)
		return;

	AShooterCharacter* Pawn = Cast<AShooterCharacter>(ShooterController->GetPawn());

	if (!Pawn)
		return;

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

	if (!Blackboard || !Pawn)
		return;

	Blackboard->SetValueAsInt(GetSelectedBlackboardKey(), Pawn->GetCurrentAmmo());
}