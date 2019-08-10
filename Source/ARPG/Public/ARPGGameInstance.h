// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyAssetManager.h"
#include "PrimaryEquip.h"
#include "ARPGGameInstance.generated.h"

/**
 * 
 */
class UDataTable;
UCLASS()
class ARPG_API UARPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:

	TArray<FPrimaryAssetType> PrimaryTypes;

	void LoadPrimaryItems();

	/**************/
public:
	virtual void Init() override;
	/**/
	

	//FORCEINLINE TArray<FItemInfoData*>& GetItemDataArray() { return ItemDataArray; }

	//FORCEINLINE TArray<FEquipData*>& GetEquipDataArray() { return EquipDataArray; }

	//FORCEINLINE TArray<FComsumeData*>& GetConsumeDataArray() { return ConsumeDataArray; }

	//FORCEINLINE TArray<FStuffData*>& GetStuffDataArray() { return StuffDataArray; }
};
