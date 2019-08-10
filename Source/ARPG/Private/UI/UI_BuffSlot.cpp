// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_BuffSlot.h"
#include "PBuff.h"
#include "Components/Image.h"

void UUI_BuffSlot::InitBuffSlot(UPBuff* InBuffInfo)
{
	FSlateBrush TempBrush;
	LocalBuffInfo = InBuffInfo;
	TempBrush.SetResourceObject(InBuffInfo->ItemIcon);
	TempBrush.ImageSize = FVector2D(64.f, 64.f);
	BuffIcon->Brush = TempBrush;
}
