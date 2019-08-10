// Fill out your copyright notice in the Description page of Project Settings.

#include "StuffGoods.h"

UStuffGoods::UStuffGoods()
{
	m_GoodsType = EGoodsType::Stuff;
}

void UStuffGoods::InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner, int32 Nums /*= 1*/)
{
	Super::InitGoods(_Info, Owner, Nums);
	StuffInfo = Cast<UPrimaryStuff>(_Info);
}

