// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimaryGoods.h"
#include "ARPG.h"
#include "PrimaryEquip.generated.h"

/**
 * 
 */
class AEquipment;
UCLASS()
class ARPG_API UPrimaryEquip : public UPrimaryGoods
{
	GENERATED_BODY()
public:

	UPrimaryEquip();

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Equipment")
		EEquipmentType EquipType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
		EEquipmentPart EquipPart;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
		TSubclassOf<AEquipment> EquipmentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
		bool bIsWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment")
		TMap<EPropertyName, float> AddtiveAttribute;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Equipment", meta = (EditCondition = "bIsWeapon"))
		TArray<FPrimaryAssetId> WeaponSkills;

};
