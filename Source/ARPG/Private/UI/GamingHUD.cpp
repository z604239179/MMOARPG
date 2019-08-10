// Fill out your copyright notice in the Description page of Project Settings.

#include "GamingHUD.h"
#include "GamingMainUI.h"

void AGamingHUD::BeginPlay()
{
	Super::BeginPlay(); 
}

bool AGamingHUD::CallInventory()
{
	return MainUIInstance->CallInventory();
	
}

bool AGamingHUD::CallCharacterPanel()
{
	
	return MainUIInstance->CallCharacterPanel();
	
}

bool AGamingHUD::CallCheatPanel()
{

	return MainUIInstance->CallCheatPanel();
}

void AGamingHUD::AddMessage(const FString& msg, const FString& InstigaterName)
{
	MainUIInstance->AddMessage(msg, InstigaterName);
}

void AGamingHUD::AddBuff(class UPBuff* BuffInfo)
{
	MainUIInstance->AddBuff(BuffInfo);
}

void AGamingHUD::RemoveBuff(class UPBuff* BuffInfo)
{
	MainUIInstance->RemoveBuff(BuffInfo);
}

void AGamingHUD::CreateUI()
{
	if (MainUIClass)
	{
		MainUIInstance = CreateWidget<UGamingMainUI, APlayerController>(Cast<APlayerController>(GetOwner()), MainUIClass);
		MainUIInstance->AddToViewport();
	}
}

void AGamingHUD::AddChild(UWidget* InWidget)
{
	MainUIInstance->AddChild(InWidget);
}

void AGamingHUD::RemoveChild(UWidget* InWidget)
{
	MainUIInstance->RemoveChild(InWidget);
}


