// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/GoodsBase.h"
#include "StuffGoods.generated.h"

/**
 * 
 */
class UPrimaryStuff;
UCLASS()
class ARPG_API UStuffGoods : public UGoodsBase
{
	GENERATED_BODY()
protected:
	UPrimaryStuff* StuffInfo;
public:
	UStuffGoods();
	virtual void InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner, int32 Nums = 1);

};
