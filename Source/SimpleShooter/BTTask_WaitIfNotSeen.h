// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_Wait.h"
#include "BTTask_WaitIfNotSeen.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API UBTTask_WaitIfNotSeen : public UBTTask_Wait
{
	GENERATED_BODY()
	
public:
	UBTTask_WaitIfNotSeen();

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
