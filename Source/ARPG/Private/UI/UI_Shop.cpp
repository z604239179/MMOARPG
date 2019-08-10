// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Shop.h"
#include "MyAssetManager.h"
#include "UI_ShopSlot.h"
#include "PrimaryGoods.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "UI_InventorySlot.h"

#define MaxColumn 7
bool UUI_Shop::Initialize()
{
	Super::Initialize();
	return true;
}

void UUI_Shop::InitShop(const TArray<FPrimaryAssetId>& GoodsList)
{
	int32 CurrentRow = 0;
	int32 CurrentColumn = 0;
	if (SlotClass)
	{
		for (auto& it : GoodsList)
		{
			UPrimaryGoods* TempGoodsInfo = UMyAssetManager::FindObjectFromId<UPrimaryGoods>(it);
			if (TempGoodsInfo)
			{
				UUI_ShopSlot* TempSlot = CreateWidget<UUI_ShopSlot, APlayerController>(GetOwningPlayer(), SlotClass);
				TempSlot->FlushSlot(TempGoodsInfo,1);
				UUniformGridSlot* TempGridSlot = ShopPanel->AddChildToUniformGrid(TempSlot);
				TempGridSlot->SetColumn(CurrentColumn);
				TempGridSlot->SetRow(CurrentRow);
				CurrentColumn++;
				if (CurrentColumn == MaxColumn)
				{
					CurrentRow++;
					CurrentColumn = 0;
				}

			}
		}
	}
}

void UUI_Shop::ClearShop()
{
	for (int32 it = 0; it < ShopPanel->GetChildrenCount(); ++it)
	{
		ShopPanel->RemoveChildAt(it);
	}
}

bool UUI_Shop::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UUI_InventorySlot* Resource = Cast<UUI_InventorySlot>(InOperation->Payload);
	if (Resource)
	{
		UGoodsBase* SoldGoods = OnwerData->Inventory[Resource->SlotIndex];
		int32 TempGold = SoldGoods->GetBasicItemInfo()->Price * SoldGoods->CurrentNum;
		if (OnwerData->DestroyItem(Resource->SlotIndex, SoldGoods->CurrentNum))
		{
			OnwerData->Gold += TempGold;
			return true;
		}
	}
	return false;
}
