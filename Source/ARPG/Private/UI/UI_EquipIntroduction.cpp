// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_EquipIntroduction.h"
#include "PrimaryEquip.h"

void UUI_EquipIntroduction::SetLocalItem(UPrimaryGoods* TargetItem)
{
	Super::SetLocalItem(TargetItem);
	EquipGoodsInfo = Cast<UPrimaryEquip>(TargetItem);
}
