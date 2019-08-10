// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_BuffPanel.h"
#include "UI_BuffSlot.h"
#include "WrapBox.h"

void UUI_BuffPanel::AddBuff(class UPBuff* BuffInfo)
{
	if (BuffSlotClass)
	{
		UUI_BuffSlot* BuffSlotTemp = CreateWidget<UUI_BuffSlot, APlayerController>(GetOwningPlayer(), BuffSlotClass);
		BuffSlotTemp->InitBuffSlot(BuffInfo);
		BuffPanel->AddChildWrapBox(BuffSlotTemp);
		BuffList.Add(BuffInfo, BuffSlotTemp);
	}
}

void UUI_BuffPanel::RemoveBuff(UPBuff* BuffInfo)
{
	BuffPanel->RemoveChild(BuffList[BuffInfo]);
	BuffList.Remove(BuffInfo);
}
