// Fill out your copyright notice in the Description page of Project Settings.

#include "ARPGGameInstance.h"


void UARPGGameInstance::LoadPrimaryItems()
{
	//TODO : 是否需要加容器装载
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


	/*测试是否成功加载*/
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
	///*让ItemDataArray中装备的DetailIndex赋值*/
	//for (int32 it = 0; it < EquipDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(EquipDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
	///*让ConsumeDataArray中消耗品的DetailIndex赋值*/
	//for (int32 it = 0; it < ConsumeDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(ConsumeDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
	///*让StuffDataArray中材料的DetailIndex赋值*/
	//for (int32 it = 0; it < StuffDataArray.Num(); ++it)
	//{
	//	ItemDataArray[(StuffDataArray[it]->ItemIndex)]->DetailIndex = it;
	//}
}
