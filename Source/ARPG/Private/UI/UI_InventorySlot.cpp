// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_InventorySlot.h"
#include "PickupBase.h"
#include "GamingPlayerState.h"
#include "DragWidget.h"
#include "DragDropOperation.h"
#include "UI_EquipmentSlot.h"
#include "UI_ShopSlot.h"

UUI_InventorySlot::UUI_InventorySlot(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	SlotType = ESlotType::Inventory;
}


void UUI_InventorySlot::OnMouseRightButtonUp()
{
	OnwerData->UseItem(SlotIndex);
	if (IntroductionPanle)
	{
		IntroductionPanle->RemoveFromViewport();
		IntroductionPanle = nullptr;
	}
}

void UUI_InventorySlot::OnMouseLeftButtonUp()
{
	OnwerData->DropItem(SlotIndex, 1);
	if (IntroductionPanle)
	{
		IntroductionPanle->RemoveFromViewport();
		IntroductionPanle = nullptr;
	}
}


bool UUI_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	UUI_SlotBase* ResourceSlot = Cast<UUI_SlotBase>(InOperation->Payload);
	switch (ResourceSlot->SlotType)
	{
	case ESlotType::Inventory:
	{
		UUI_InventorySlot* Resource = Cast<UUI_InventorySlot>(InOperation->Payload);

		if (SlotPtr)
		{
			UGoodsBase* TempGoods = OnwerData->GetInventory()[SlotIndex];
			OnwerData->GetInventory()[SlotIndex] = OnwerData->GetInventory()[Resource->SlotIndex];
			OnwerData->GetInventory()[Resource->SlotIndex] = TempGoods;
		}
		else
		{
			OnwerData->GetInventory()[SlotIndex] = OnwerData->GetInventory()[Resource->SlotIndex];
			OnwerData->GetInventory()[Resource->SlotIndex] = nullptr;
		}
		OnwerData->OnInventoryChanged.Broadcast(OnwerData->GetInventory()[SlotIndex], SlotIndex);
		OnwerData->OnInventoryChanged.Broadcast(OnwerData->GetInventory()[Resource->SlotIndex], Resource->SlotIndex);
		return true;


	}
	break;
	case ESlotType::Equipment:
	{
		UUI_EquipmentSlot* EquipResource = Cast<UUI_EquipmentSlot>(InOperation->Payload);

		OnwerData->GetItem(OnwerData->UnEquip(EquipResource->GetEquipmentInfo()->EquipPart));
		return true;

	}
	break;
	case ESlotType::Shop:
	{
		UUI_ShopSlot* ShopResource = Cast<UUI_ShopSlot>(InOperation->Payload);
		ShopResource->BuyGoods();
		return true;
	}
	break;
	default:
		break;
	}


	return false;
}
