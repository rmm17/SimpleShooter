// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/ProgressBar.h"

bool UHealthWidget::Initialize()
{
	bool bRetValue = Super::Initialize();

	if (WidgetTree)
	{
		HealthBar = WidgetTree->FindWidget<UProgressBar>(TEXT("HealthBar_1"));
	}

	return bRetValue;
}

void UHealthWidget::UpdateHealthPercent(float HealthPercent)
{
	HealthBar->SetPercent(HealthPercent);
}