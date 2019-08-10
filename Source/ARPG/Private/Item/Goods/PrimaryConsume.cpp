// Fill out your copyright notice in the Description page of Project Settings.

#include "PrimaryConsume.h"
#include "MyAssetManager.h"
#include "ConsumeGoods.h"

UPrimaryConsume::UPrimaryConsume()
{

	m_Type = UMyAssetManager::ConsumeType;
	mGoodsType = EGoodsType::Consume;
	GoodsClass = UConsumeGoods::StaticClass();

}
