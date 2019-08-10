// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_Introduction.h"
#include "UI_EquipIntroduction.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UUI_EquipIntroduction : public UUI_Introduction
{
	GENERATED_BODY()
protected:
	class UPrimaryEquip* EquipGoodsInfo;
public:
	virtual void SetLocalItem(UPrimaryGoods* TargetItem) override;
};
