// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToWhileNotSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_MoveToWhileNotSeen : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToWhileNotSeen();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
