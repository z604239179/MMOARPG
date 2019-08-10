// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/UI_SlotBase.h"
#include "UI_ShopSlot.generated.h"

/**
 * 
 */
class UPrimaryGoods;
UCLASS()
class ARPG_API UUI_ShopSlot : public UUI_SlotBase
{
	GENERATED_BODY()
public:
	UUI_ShopSlot(const FObjectInitializer& ObjectInitializer);

	virtual void OnMouseRightButtonUp() override;
	void BuyGoods();
};
