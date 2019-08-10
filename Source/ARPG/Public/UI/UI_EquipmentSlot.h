// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_SlotBase.h"
#include "UI_EquipmentSlot.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_EquipmentSlot : public UUI_SlotBase
{
	GENERATED_BODY()
public:
	UUI_EquipmentSlot(const FObjectInitializer& ObjectInitializer);
	class UPrimaryEquip* GetEquipmentInfo();

};
