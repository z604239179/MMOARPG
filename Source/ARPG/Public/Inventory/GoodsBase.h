// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GoodsBase.generated.h"

/**
 * 
 */

#define NULLITEM 0
class APlayerCharacter;
UCLASS(Abstract)
class ARPG_API UGoodsBase : public UObject
{
	GENERATED_BODY()
private:
	class UPrimaryGoods* ItemInfo;

protected:
	APlayerCharacter* GoodsOwner;

public:

	void SetOwner(APlayerCharacter* Owner) { GoodsOwner = Owner; }

	/*仅在服务器上执行*/
	virtual void InitGoods(UPrimaryGoods* _Info, APlayerCharacter* Owner,int32 Nums = 1);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		EGoodsType m_GoodsType;
	/*物品当前数量*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		uint8 CurrentNum;


	FORCEINLINE UPrimaryGoods* GetBasicItemInfo() const { return ItemInfo; }

	virtual bool UseItem() { return false; }
};
