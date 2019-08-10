// Fill out your copyright notice in the Description page of Project Settings.

#include "GoodsBase.h"

void UGoodsBase::InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner, int32 Nums)
{
	ItemInfo = _Info;
	GoodsOwner = Owner;
	CurrentNum = Nums;
}
