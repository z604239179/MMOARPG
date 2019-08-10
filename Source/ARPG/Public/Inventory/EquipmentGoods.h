// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Inventory/GoodsBase.h"
#include "EquipmentGoods.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UEquipmentGoods : public UGoodsBase
{
	GENERATED_BODY()
protected:

	class UPrimaryEquip* ItemInfo;
public:

	UEquipmentGoods();

	FORCEINLINE UPrimaryEquip* GetEquipmentInfo() { return this->ItemInfo; }

	virtual void InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner,int32 Nums = 1) override;

	virtual bool UseItem() override;

	void OnEquip();

	void OnUnEquip();

};
