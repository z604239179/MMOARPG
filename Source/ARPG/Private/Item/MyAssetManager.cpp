// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAssetManager.h"
#include "PrimaryItem.h"

const FPrimaryAssetType UMyAssetManager::PCharacterSkillType = TEXT("PCharacterSkillType");
const FPrimaryAssetType UMyAssetManager::PWeaponSkillType = TEXT("PWeaponSkillType");
const FPrimaryAssetType UMyAssetManager::PPassiveSkillType = TEXT("PPassiveSkillType");
const FPrimaryAssetType UMyAssetManager::PBuffType = TEXT("PBuffType");
const FPrimaryAssetType UMyAssetManager::EquipType = TEXT("EquipType");
const FPrimaryAssetType UMyAssetManager::ConsumeType = TEXT("ConsumeType");
const FPrimaryAssetType UMyAssetManager::StuffType = TEXT("StuffType");
const FPrimaryAssetType UMyAssetManager::NPCType = TEXT("NPCType");
const FPrimaryAssetType UMyAssetManager::MonsterType = TEXT("MonsterType");

const TArray<FPrimaryAssetType> UMyAssetManager::AllItemTypes = { PCharacterSkillType,PWeaponSkillType,PPassiveSkillType,PBuffType,EquipType,ConsumeType,StuffType,NPCType,MonsterType };

UMyAssetManager& UMyAssetManager::Get()
{
	UMyAssetManager* Singleton = Cast<UMyAssetManager>(GEngine->AssetManager);

	if (Singleton)
	{
		return *Singleton;
	}
	else
	{
		return *NewObject<UMyAssetManager>(); // never calls this
	}

}

class UPrimaryItem* UMyAssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UPrimaryItem* LoadedItem = Cast<UPrimaryItem>(ItemPath.TryLoad());

	return LoadedItem;
}
