// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/GoodsBase.h"
#include "ConsumeGoods.generated.h"

/**
 * 
 */
class UPrimaryConsume;
UCLASS()
class ARPG_API UConsumeGoods : public UGoodsBase
{
	GENERATED_BODY()
protected:
	UPrimaryConsume* ConsumeInfo;
public:
	UConsumeGoods();

	virtual void InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner, int32 Nums = 1);

	virtual bool UseItem() override;
};
