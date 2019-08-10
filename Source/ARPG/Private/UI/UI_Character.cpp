// Fill out your copyright notice in the Description peequiptypeage of Project Settings.

#include "UI_Character.h"
#include "UI_EquipmentSlot.h"
#include "UI_AttributeItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "CharacterInfoBase.h"
#include "DragWidget.h"
#include "UI_InventorySlot.h"
#include "DragDropOperation.h"

void UUI_Character::OnValueChanged(EPropertyName ChangedName, const FPropertesValue& ChangedValue)
{
	AttributeInfos[ChangedName].ItemRef->Attribute_Value->SetText(FText::AsNumber(ChangedValue.BasicValue + ChangedValue.AddtiveValue));
}

void UUI_Character::HandleEquipChanged(UEquipmentGoods* ChangedGoods, EEquipmentPart ChangedPart)
{
	EquipSlotMap[ChangedPart]->FlushSlot(ChangedGoods);
}

UUI_Character::UUI_Character(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer)
{
	for (int32 it = 0; it < (int32)EPropertyName::MAX; ++it)
	{
		AttributeInfos.Add((EPropertyName)it, FAttributeItemInfo());
	}
}

bool UUI_Character::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	UUI_InventorySlot* Resource = Cast<UUI_InventorySlot>(InOperation->Payload);
	if (Resource)
	{
		UEquipmentGoods* TempGoods = Cast<UEquipmentGoods>(OnwerData->GetInventory()[Resource->SlotIndex]);
		if (TempGoods)
		{
			OnwerData->UseItem(Resource->SlotIndex);
			return true;
		}

	}

	return false;
}

bool UUI_Character::Initialize()
{
	Super::Initialize();
	
	if (OnwerData)
	{
		OnwerData->OnEquipmentChanged.AddUniqueDynamic(this, &UUI_Character::HandleEquipChanged);
		EquipSlotMap.Add(EEquipmentPart::Head, HeadSlot);
		EquipSlotMap.Add(EEquipmentPart::Ring, RingSlot);
		EquipSlotMap.Add(EEquipmentPart::NeckLace, NecklaceSlot);
		EquipSlotMap.Add(EEquipmentPart::Armor, ArmorSlot);
		EquipSlotMap.Add(EEquipmentPart::Pant, PantSlot);
		EquipSlotMap.Add(EEquipmentPart::Shoes, ShoesSlot);
		EquipSlotMap.Add(EEquipmentPart::Left, LeftSlot);
		EquipSlotMap.Add(EEquipmentPart::Right, RightSlot);

// 		HeadSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Head]));
// 		RingSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Ring]));
// 		NecklaceSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::NeckLace]));
// 		ArmorSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Armor]));
// 		PantSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Pant]));
// 		ShoesSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Shoes]));
// 		LeftSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Left]));
// 		RightSlot->SetSlot(&(OnwerData->EquipmentInfoMap[EEquipmentPart::Right]));

		TArray<FPropertesValue>& TempAttribute = OnwerData->GetAttributes();
		UClass* loadClass  = StaticLoadClass(UUI_AttributeItem::StaticClass(), NULL, TEXT("WidgetBlueprint'/Game/UI/UMG/UMG_AttributeItem.UMG_AttributeItem_C'"));
		if (loadClass)
		{
			uint8 ItCount = 0;
			for (auto& it : TempAttribute)
			{
				UUI_AttributeItem* TempWidget =  CreateWidget<UUI_AttributeItem, APlayerController>(GetOwningPlayer(), loadClass);
				TempWidget->Attribute_Icon->SetBrush(AttributeInfos[(EPropertyName)ItCount].AttributeBrush);
				TempWidget->Attribute_Name->SetText(AttributeInfos[(EPropertyName)ItCount].AttributeName);
				TempWidget->Attribute_Value->SetText(FText::AsNumber(it.BasicValue + it.AddtiveValue));
				AttributeInfos[(EPropertyName)ItCount].ItemRef = TempWidget;
				AttributeBox->AddChild(TempWidget);
				++ItCount;
			}

		}

		OnwerData->ValueChangedHandle.AddDynamic(this, &UUI_Character::OnValueChanged);

	}


	return true;
}
