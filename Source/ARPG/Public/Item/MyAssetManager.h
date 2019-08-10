// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static const FPrimaryAssetType PCharacterSkillType;
	static const FPrimaryAssetType PWeaponSkillType;
	static const FPrimaryAssetType PPassiveSkillType;
	static const FPrimaryAssetType PBuffType;
	static const FPrimaryAssetType EquipType;
	static const FPrimaryAssetType ConsumeType;
	static const FPrimaryAssetType StuffType;
	static const FPrimaryAssetType NPCType;
	static const FPrimaryAssetType MonsterType;

	static const TArray<FPrimaryAssetType> AllItemTypes;

	/** Returns the current AssetManager object */
	static UMyAssetManager& Get();

	template<typename T>
	static T* FindObjectFromId(const FPrimaryAssetId& _InId);

	class UPrimaryItem* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId);
};

template<typename T>
T* UMyAssetManager::FindObjectFromId(const FPrimaryAssetId& _InId)
{
	T* RetObject = Cast<T>(UAssetManager::Get().GetPrimaryAssetObject(_InId));
	if (RetObject)
		return RetObject;

	return nullptr;
}
