// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_HealthBar.h"
#include "Components/ProgressBar.h"
#include "CharacterBase.h"

float UUI_HealthBar::HealthDelegate()
{
	return OwnPawn->GetHealthComponent()->GetHealthPercent();
}

float UUI_HealthBar::ManaDelegate()
{
	return OwnPawn->GetHealthComponent()->GetManaPercent();
}


bool UUI_HealthBar::Initialize()
{
	Super::Initialize();
	OwnPawn = Cast<ACharacterBase>(GetOwningPlayerPawn());
	if (OwnPawn)
	{
		HealthBar->PercentDelegate.BindUFunction(this, FName("HealthDelegate"));
		ManaBar->PercentDelegate.BindUFunction(this, FName("ManaDelegate"));
	}
	return true;
}

