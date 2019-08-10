// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_EquipmentSlot.h"
#include "Components/Image.h"

UUI_EquipmentSlot::UUI_EquipmentSlot(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	SlotType = ESlotType::Equipment;
}


UPrimaryEquip* UUI_EquipmentSlot::GetEquipmentInfo()
{
	return Cast<UPrimaryEquip>(SlotPtr);
}

