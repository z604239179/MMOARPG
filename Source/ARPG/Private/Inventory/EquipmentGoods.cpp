// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentGoods.h"
#include "PrimaryGoods.h"

UEquipmentGoods::UEquipmentGoods()
{
	m_GoodsType = EGoodsType::Equipment;
}

void UEquipmentGoods::InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner,int32 Nums)
{
	Super::InitGoods(_Info, Owner, Nums);
	ItemInfo = Cast<UPrimaryEquip>(_Info);
}

bool UEquipmentGoods::UseItem()
{
	if (GoodsOwner)
	{
		return GoodsOwner->GetPlayerInfoData()->Equip(this);

	}

	return false;
}

void UEquipmentGoods::OnEquip()
{
	/*装备时增加属性*/
	if (GoodsOwner)
	{
		for (auto& it : ItemInfo->AddtiveAttribute)
		{
			/*	float TempValue = OwnPawn->GetCurrentInfoData()->GetAttributefromName(it.Key) - OwnPawn->GetCurrentInfoData()->GetBasicAttributes(it.Key);
				OwnPawn->GetCurrentInfoData()->SetAttributefromName(it.Key, it.Value + TempValue);*/

			GoodsOwner->GetCurrentInfoData()->AddAttributefromName(it.Key, it.Value);
		}
	}
}

void UEquipmentGoods::OnUnEquip()
{
	if (GoodsOwner)
	{
		for (auto& it : ItemInfo->AddtiveAttribute)
		{
			/*float TempValue = OwnPawn->GetCurrentInfoData()->GetAttributefromName(it.Key);
			OwnPawn->GetCurrentInfoData()->SetAttributefromName(it.Key, TempValue - it.Value);
			*/
			GoodsOwner->GetCurrentInfoData()->SubAttributefromName(it.Key, it.Value);
		}
	}
}
