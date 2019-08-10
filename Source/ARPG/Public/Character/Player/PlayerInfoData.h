// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterInfoBase.h"
#include "ARPG.h"
#include "PlayerInfoData.generated.h"

/**
 * 
 */

class UGoodsBase;
class UEquipmentGoods;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnInventoryChanged, UGoodsBase*,ChangedGoods,int32,ChangedIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEquipmentChanged, UEquipmentGoods*, ChangedGoods, EEquipmentPart, ChangedPart);


UCLASS()
class ARPG_API APlayerInfoData : public ACharacterInfoBase
{
	GENERATED_BODY()
public:
	APlayerInfoData();

protected:
	FString PlayerName;


	int32 InventoryCapcity;

	int32 RemainCapcity;

	UFUNCTION(Server, WithValidation, Reliable)
		void SpawnDropActor(int32 SlotIndex, int32 Nums);
public:
/*Inventory*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TArray<UGoodsBase*> Inventory;
 
	UFUNCTION(Client,Reliable)
	void PickupItem(APickupBase* InItem);

	UFUNCTION(BlueprintCallable)
		bool DropItem(int32 SlotIndex, int32 DropNums);

	UFUNCTION(BlueprintCallable)
		bool UseItem(int32 SlotIndex);

	bool GetItem(class UPrimaryGoods* GoodsInfo,int32 Nums);
	bool GetItem(class UGoodsBase* InGoods);

	bool DestroyItem(int32 SlotIndex, int32 DestroyNums);

	FOnInventoryChanged OnInventoryChanged;
	/**********/

	/*Equipment*/


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TMap<EEquipmentPart, UEquipmentGoods*> EquipmentInfoMap;

	bool Equip(UEquipmentGoods* InEquip);


	UEquipmentGoods* UnEquip(EEquipmentPart UnEquipPart);

	TArray<UGoodsBase*>& GetInventory()
	{
		return Inventory;
	}

	FOnEquipmentChanged OnEquipmentChanged;
	/*************/

	FORCEINLINE const FString& GetPlayerName() { return PlayerName; }
	void SetPlayerName(FString InName) { PlayerName = InName; }

public:
	/*Ohters Propertes*/
	int32 Gold = 0;
};

