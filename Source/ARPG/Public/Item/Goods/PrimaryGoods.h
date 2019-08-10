// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PrimaryItem.h"
#include "PrimaryGoods.generated.h"

/**
 * 
 */

UENUM()
enum class EQuality :uint8
{
	Normal,		/*白色*/
	Delicate,	/*绿色*/
	Rare,		/*蓝色*/
	Epic,		/*紫色*/
	Legend,		/*橙色*/

};

UENUM()
enum class EGoodsType : uint8
{
	None,
	Equipment,
	Consume,
	Stuff,
};

class UGoodsBase;
UCLASS(Abstract)
class ARPG_API UPrimaryGoods : public UPrimaryItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		EQuality mQuality = EQuality::Normal;
	/*物品最大堆叠数量*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
		uint8 MaxNum=1;

	/*物品价格*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item",meta = (ClampMin=0))
		int32 Price;

	EGoodsType mGoodsType;
	TSubclassOf<UGoodsBase> GoodsClass;
};
