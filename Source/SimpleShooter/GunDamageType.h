// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "GunDamageType.generated.h"

/**
 * 
 */
UCLASS(const, Blueprintable, BlueprintType)
class SIMPLESHOOTER_API UGunDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	/** Damage type identifying if the head of a character was hit */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DamageType)
	uint32 GunHeadShot:1;
};
