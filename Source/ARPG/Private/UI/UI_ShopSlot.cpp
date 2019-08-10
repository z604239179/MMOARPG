// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_ShopSlot.h"
#include "PrimaryGoods.h"

UUI_ShopSlot::UUI_ShopSlot(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	SlotType = ESlotType::Shop;
}



void UUI_ShopSlot::OnMouseRightButtonUp()
{
	BuyGoods();
}


void UUI_ShopSlot::BuyGoods()
{
	if (OnwerData->Gold >= SlotPtr->Price)
	{
		if (OnwerData->GetItem(SlotPtr, 1))
		{
			OnwerData->Gold -= SlotPtr->Price;
		}
	}
}

