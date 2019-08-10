// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryEquip.h"
#include "MyAssetManager.h"
#include "EquipmentGoods.h"
UPrimaryEquip::UPrimaryEquip()
{
	m_Type = UMyAssetManager::EquipType;
	mGoodsType = EGoodsType::Equipment;
	GoodsClass = UEquipmentGoods::StaticClass();
	bIsWeapon = false;
}
