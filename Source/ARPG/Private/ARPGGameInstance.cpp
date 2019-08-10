// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGGameInstance.h"


void UARPGGameInstance::LoadPrimaryItems()
{
	//TODO : �Ƿ���Ҫ������װ��
	UMyAssetManager& TempManager = UMyAssetManager::Get();
	PrimaryTypes = TempManager.AllItemTypes;
	for (auto& Type : PrimaryTypes)
	{
		FPrimaryAssetType TempType = Type;
		TArray<FPrimaryAssetId> IdList;
		if (TempManager.GetPrimaryAssetIdList(TempType, IdList))
		{

			TempManager.LoadPrimaryAssets(IdList);
		}
	}


	/*�����Ƿ�ɹ�����*/
	/*for (auto Tempi : DataIdMap)
	{
		for (auto Tempj : Tempi.Value)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, Tempj.ToString());
		}
	}*/
}

void UARPGGameInstance::Init()
{
	Super::Init();
	LoadPrimaryItems();
	//if (ItemDataTable)
	//{
	//	ItemDataTable->GetAllRows("ItemData", ItemDataArray);
	//}
	//if (EquipDataTable)
	//{
	//	EquipDataTable->GetAllRows("EquipData", EquipDataArray);
	//}
	//if (ConsumeDataTable)
	//{
	//	ConsumeDataTable->GetAllRows("ConsumeData", ConsumeDataArray);
	//}
	//if (StuffDataTable)
	//{
	//	StuffDataTable->GetAllRows("StuffData", StuffDataArray);
	//}
	///*��ItemDataArray��װ����DetailIndex��ֵ*/
	//for (int32 it = 0; it < EquipDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(EquipDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
	///*��ConsumeDataArray������Ʒ��DetailIndex��ֵ*/
	//for (int32 it = 0; it < ConsumeDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(ConsumeDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
	///*��StuffDataArray�в��ϵ�DetailIndex��ֵ*/
	//for (int32 it = 0; it < StuffDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(StuffDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
}
