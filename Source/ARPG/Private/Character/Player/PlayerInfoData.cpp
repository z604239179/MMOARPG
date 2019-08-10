// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerInfoData.h"
#include "PickupBase.h"
#include "ARPGGameModeBase.h"
#include "PlayerCharacter.h"
#include "Inventory/GoodsBase.h"
#include "Inventory/EquipmentGoods.h"
#include "GamingHUD.h"
#include "Net/UnrealNetwork.h"

APlayerInfoData::APlayerInfoData()
{
	InventoryCapcity = 28;
	RemainCapcity = InventoryCapcity;
	Inventory.Init(nullptr, InventoryCapcity);
	for (int32 it = 0; it < (int32)EEquipmentPart::Max; ++it)
	{
		EquipmentInfoMap.Add((EEquipmentPart)it, nullptr);
	}

}





void APlayerInfoData::SpawnDropActor_Implementation(int32 SlotIndex, int32 Nums)
{
	/*����һ����Ʒ*/
	AARPGGameModeBase* MyGamemode = Cast<AARPGGameModeBase>(GetWorld()->GetAuthGameMode());
	MyGamemode->SpawnItem(Inventory[SlotIndex]->GetBasicItemInfo()->GetPrimaryAssetId(), Nums,
		FTransform(GetPawn()->GetActorLocation() + GetPawn()->GetActorForwardVector()*100.f), GetController());
}

bool APlayerInfoData::SpawnDropActor_Validate(int32 SlotIndex, int32 Nums)
{
	return true;
}






void APlayerInfoData::PickupItem_Implementation(APickupBase* InItem)
{
	for (auto& it : InItem->LootsList)
	{
		GetItem(UMyAssetManager::FindObjectFromId<UPrimaryGoods>(it.GoodsID), it.Nums);
	}
}





bool APlayerInfoData::DropItem(int32 SlotIndex, int32 DropNums)
{
	/*���ʺϷ�*/
	if (SlotIndex < Inventory.Num()&& Inventory[SlotIndex])
	{
		/*������������ӵ����������false������ʧ��*/
		if (DropNums > Inventory[SlotIndex]->CurrentNum)
		{
			return false;
		}

		SpawnDropActor(SlotIndex, DropNums);

		/*��������С��ӵ����������*/
		if (DropNums < Inventory[SlotIndex]->CurrentNum)
		{
			Inventory[SlotIndex]->CurrentNum -= DropNums;
			OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
		}

		/*������������ӵ����������*/
		else if (DropNums == Inventory[SlotIndex]->CurrentNum)
		{
			Inventory[SlotIndex] = nullptr;
			OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
			++RemainCapcity;
		}

		return true;
	}
	return false;
}


bool APlayerInfoData::UseItem(int32 SlotIndex)
{

	if (Inventory[SlotIndex])
	{
		if (Inventory[SlotIndex]->UseItem())
		{
			--Inventory[SlotIndex]->CurrentNum;
			OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
			/*���ʣ��0��*/
			if (Inventory[SlotIndex]->CurrentNum <= 0)
			{
				Inventory[SlotIndex] = nullptr;
				OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
				++RemainCapcity;
				return true;
			}
		}
	}

	return false;
}

bool APlayerInfoData::GetItem(UPrimaryGoods* GoodsInfo, int32 Nums)
{
	for (int32 it = 0; it < Inventory.Num(); ++it)
	{
		/*�������ͬһ��Ʒ,�ж��ǲ��ǿո�*/
		if (Inventory[it] == nullptr)
		{//TODO:Owner����
			UGoodsBase* TempGoods = NewObject<UGoodsBase>(GetWorld(), GoodsInfo->GoodsClass);
			TempGoods->InitGoods(GoodsInfo,Cast<APlayerCharacter>(Cast<AController>(GetOwner())->GetPawn()), Nums);
			Inventory[it] = TempGoods;
			OnInventoryChanged.Broadcast(TempGoods, it);
			--RemainCapcity;
			/*�����ǰ�����������ѵ�����*/
			if (TempGoods->CurrentNum > GoodsInfo->MaxNum)
			{
				int32 OverNum = TempGoods->CurrentNum - GoodsInfo->MaxNum;

				Inventory[it]->CurrentNum = GoodsInfo->MaxNum;
				OnInventoryChanged.Broadcast(Inventory[it], it);
				Nums = OverNum;
				continue;
			}
			/*�����ǰ�����������ѵ�����*/
			else
			{
				return true;
			}
		}



		/*�ж��Ƿ���ͬһ��Ʒ*/
		else if (Inventory[it]->GetBasicItemInfo()->GetPrimaryAssetId() ==GoodsInfo->GetPrimaryAssetId())
		{
			/*���δ�ﵽ��������*/
			if (Inventory[it]->CurrentNum < Inventory[it]->GetBasicItemInfo()->MaxNum)
			{
				int32 OverlapNum = Inventory[it]->GetBasicItemInfo()->MaxNum - Inventory[it]->CurrentNum;
				/*������Ӻ󲻳�����������*/
				if (OverlapNum >= Nums)
				{
					Inventory[it]->CurrentNum += Nums;
					OnInventoryChanged.Broadcast(Inventory[it], it);
					return true;
				}
				/*������Ӻ󳬹���������*/
				else
				{
					Inventory[it]->CurrentNum = Inventory[it]->GetBasicItemInfo()->MaxNum;
					OnInventoryChanged.Broadcast(Inventory[it], it);
					Nums -= OverlapNum;
					continue;
				}
			}
			/*����ﵽ�˵�������*/
			else
			{
				continue;
			}
		}

		/*�Ȳ���ͬһ��ƷҲ���ǿո������*/
	}


	/*��������*/
	return false;
}



bool APlayerInfoData::GetItem(UGoodsBase* InGoods)
{
	for (int32 it = 0; it < Inventory.Num(); ++it)
	{
		/*�������ͬһ��Ʒ,�ж��ǲ��ǿո�*/
		if (Inventory[it] == nullptr)
		{//TODO:Owner����
			InGoods->SetOwner(Cast<APlayerCharacter>(Cast<AController>(GetOwner())->GetPawn()));
			Inventory[it] = InGoods;
			OnInventoryChanged.Broadcast(Inventory[it], it);
			--RemainCapcity;
			/*�����ǰ�����������ѵ�����*/
			if (InGoods->CurrentNum > InGoods->GetBasicItemInfo()->MaxNum)
			{
				int32 OverNum = InGoods->CurrentNum - InGoods->GetBasicItemInfo()->MaxNum;

				Inventory[it]->CurrentNum = InGoods->GetBasicItemInfo()->MaxNum;
				OnInventoryChanged.Broadcast(Inventory[it], it);
				InGoods->CurrentNum = OverNum;
				continue;
			}
			/*�����ǰ�����������ѵ�����*/
			else
			{
				return true;
			}
		}



		/*�ж��Ƿ���ͬһ��Ʒ*/
		else if (Inventory[it]->GetBasicItemInfo()->GetPrimaryAssetId() == InGoods->GetBasicItemInfo()->GetPrimaryAssetId())
		{
			/*���δ�ﵽ��������*/
			if (Inventory[it]->CurrentNum < Inventory[it]->GetBasicItemInfo()->MaxNum)
			{
				int32 OverlapNum = Inventory[it]->GetBasicItemInfo()->MaxNum - Inventory[it]->CurrentNum;
				/*������Ӻ󲻳�����������*/
				if (OverlapNum >= InGoods->CurrentNum)
				{
					Inventory[it]->CurrentNum += InGoods->CurrentNum;
					OnInventoryChanged.Broadcast(Inventory[it], it);
					return true;
				}
				/*������Ӻ󳬹���������*/
				else
				{
					Inventory[it]->CurrentNum = Inventory[it]->GetBasicItemInfo()->MaxNum;
					OnInventoryChanged.Broadcast(Inventory[it], it);
					InGoods->CurrentNum -= OverlapNum;
					continue;
				}
			}
			/*����ﵽ�˵�������*/
			else
			{
				continue;
			}
		}

		/*�Ȳ���ͬһ��ƷҲ���ǿո������*/
	}


	/*��������*/
	return false;
}

bool APlayerInfoData::DestroyItem(int32 SlotIndex, int32 DestroyNums)
{
	/*���ʺϷ�*/
	if (SlotIndex < Inventory.Num())
	{
		/*������������ӵ����������false������ʧ��*/
		if (DestroyNums > Inventory[SlotIndex]->CurrentNum)
		{
			return false;
		}

		/*��������С��ӵ����������*/
		if (DestroyNums < Inventory[SlotIndex]->CurrentNum)
		{
			Inventory[SlotIndex]->CurrentNum -= DestroyNums;
			OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
		}

		/*������������ӵ����������*/
		else if (DestroyNums == Inventory[SlotIndex]->CurrentNum)
		{
			Inventory[SlotIndex] = nullptr;
			OnInventoryChanged.Broadcast(Inventory[SlotIndex], SlotIndex);
			++RemainCapcity;
		}

		return true;
	}
	return false;
}

bool APlayerInfoData::Equip(UEquipmentGoods* InEquip)
{
	APlayerCharacter* MyPawn = Cast<APlayerCharacter>(GetPawn());
	UEquipmentGoods* TempEquiped =  nullptr;

	/*˫������*/
	if (InEquip->GetEquipmentInfo()->EquipType > EEquipmentType::TwoHand)
	{
		if (EquipmentInfoMap[EEquipmentPart::Left])
		{
			if (RemainCapcity < 1)
			{
				return false;
			}
			TempEquiped = UnEquip(EEquipmentPart::Left);
			GetItem(TempEquiped);
			//TempEquiped->OnUnEquip(get)
		}

		if (EquipmentInfoMap[EEquipmentPart::Right])
		{
			if (RemainCapcity < 1)
			{
				return false;
			}
			TempEquiped = UnEquip(EEquipmentPart::Right);
			GetItem(TempEquiped);
		}

		EquipmentInfoMap[EEquipmentPart::Left] = InEquip;
		EquipmentInfoMap[EEquipmentPart::Right] = InEquip;

		OnEquipmentChanged.Broadcast(InEquip, EEquipmentPart::Left);
		OnEquipmentChanged.Broadcast(InEquip, EEquipmentPart::Right);

	}
	/*��˫������*/
	else
	{

		if (EquipmentInfoMap[InEquip->GetEquipmentInfo()->EquipPart])
		{
			if (RemainCapcity >= 1)
			{
				TempEquiped = UnEquip(InEquip->GetEquipmentInfo()->EquipPart);
				GetItem(TempEquiped);
			}
			else
			{
				return false;
			}
		}

		EquipmentInfoMap[InEquip->GetEquipmentInfo()->EquipPart] = InEquip;
		OnEquipmentChanged.Broadcast(InEquip, InEquip->GetEquipmentInfo()->EquipPart);
	}
	 MyPawn->GetEquipmentComp()->Equip(InEquip->GetEquipmentInfo()->GetPrimaryAssetId());
	 InEquip->OnEquip();
	 return true;
}



UEquipmentGoods* APlayerInfoData::UnEquip(EEquipmentPart UnEquipPart)
{
	UEquipmentGoods* RetEquip = EquipmentInfoMap[UnEquipPart];

	if (EquipmentInfoMap[UnEquipPart]->GetEquipmentInfo()->EquipType > EEquipmentType::TwoHand)
	{
		
		EquipmentInfoMap[EEquipmentPart::Left] = nullptr;
		EquipmentInfoMap[EEquipmentPart::Right] = nullptr;

		OnEquipmentChanged.Broadcast(nullptr, EEquipmentPart::Left);
		OnEquipmentChanged.Broadcast(nullptr, EEquipmentPart::Right);

		Cast<ACharacterBase>(GetPawn())->GetEquipmentComp()->UnEquip(EEquipmentPart::Left);
		Cast<ACharacterBase>(GetPawn())->GetEquipmentComp()->UnEquip(EEquipmentPart::Right);

	}
	else
	{
		EquipmentInfoMap[UnEquipPart] = nullptr;
		OnEquipmentChanged.Broadcast(nullptr, UnEquipPart);
		Cast<ACharacterBase>(GetPawn())->GetEquipmentComp()->UnEquip(UnEquipPart);
	}
	RetEquip->CurrentNum = 1;
	RetEquip->OnUnEquip();
	return RetEquip;
}



