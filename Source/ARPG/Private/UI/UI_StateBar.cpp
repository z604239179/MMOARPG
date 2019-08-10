// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_StateBar.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerCharacter.h"

float UUI_StateBar::GetHealthPer()
{
	return MyPawn->GetHealthComponent()->GetHealthPercent();
}

float UUI_StateBar::GetManaPer()
{
	return MyPawn->GetHealthComponent()->GetManaPercent();
}

bool UUI_StateBar::Initialize()
{
	Super::Initialize();
	MyPawn = GetOwningPlayerPawn<APlayerCharacter>();
	HealthProgress->PercentDelegate.BindUFunction(this, FName("GetHealthPer"));
	ManaProgress->PercentDelegate.BindUFunction(this, FName("GetManaPer"));
	return true;
}
