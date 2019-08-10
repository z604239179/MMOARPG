// Fill out your copyright notice in the Description page of Project Settings.

#include "UIBase.h"

UUIBase::UUIBase(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{

}

bool UUIBase::Initialize()
{
	Super::Initialize();
	if (GetOwningPlayer<AMyPlayerController>())
	{
		OnwerData = GetOwningPlayer<AMyPlayerController>()->MyData;
	}
	return true;

}

