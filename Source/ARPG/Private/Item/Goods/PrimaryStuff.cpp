// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryStuff.h"
#include "MyAssetManager.h"
#include "StuffGoods.h"

UPrimaryStuff::UPrimaryStuff()
{

	GoodsClass = UStuffGoods::StaticClass();
	mGoodsType = EGoodsType::Stuff;
	m_Type = UMyAssetManager::StuffType;
}
