// Fill out your copyright notice in the Description page of Project Settings.

#include "UI_Inventory.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UI_InventorySlot.h"

UUI_Inventory::UUI_Inventory(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	InvetoryRow = 4;
	InvetoryColumn = 7;
}

FText UUI_Inventory::GoldDelegate()
{
	return FText::AsNumber(OnwerData->Gold);
}

void UUI_Inventory::HandleClosed()
{
	GetOwningPlayer()->bShowMouseCursor = false;
	GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	SetVisibility(ESlateVisibility::Hidden);
}

void UUI_Inventory::HandleInventoryChanged(UGoodsBase* ChangedGoods, int32 ChangedIndex)
{
	UUI_InventorySlot* ChangedSlot = Cast<UUI_InventorySlot>(InventoryPanel->GetChildAt(ChangedIndex));
	ChangedSlot->FlushSlot(ChangedGoods);
}

bool UUI_Inventory::Initialize()
{
	Super::Initialize();
	if (OnwerData)
	{
		Block_Gold->TextDelegate.BindUFunction(this, FName("GoldDelegate"));
		if (SlotClass)
		{
			OnwerData->OnInventoryChanged.AddUniqueDynamic(this, &UUI_Inventory::HandleInventoryChanged);
			for (int32 ItRow = 0; ItRow < InvetoryRow; ++ItRow)
			{
				for (int32 ItColumn = 0; ItColumn < InvetoryColumn; ++ItColumn)
				{
					UUI_InventorySlot* TempInventroySlot = CreateWidget<UUI_InventorySlot,APlayerController>(GetOwningPlayer(), SlotClass);
					TempInventroySlot->SlotIndex = ItRow * InvetoryColumn + ItColumn;

					UUniformGridSlot* TempSlot = InventoryPanel->AddChildToUniformGrid(TempInventroySlot);

					TempSlot->SetRow(ItRow);
					TempSlot->SetColumn(ItColumn);
				}
			}
		}
	}

	Button_Close->OnClicked.AddUniqueDynamic(this, &UUI_Inventory::HandleClosed);
	return true;
}

