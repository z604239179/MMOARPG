// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/AIBase.h"
#include "NPC.generated.h"

/**
 * 
 */
class APickupBase;
UCLASS()
class ARPG_API ANPC : public AAIBase
{
	GENERATED_BODY()

protected:
	class UPrimaryNPC* NPCInfo;
	TMap<APickupBase*, int32> GoodsList;
public:
	virtual void BeginPlay() override;

	virtual void InitCharacter() override;

	void Buy(int32 GoodsIndex);
	void Sell(APickupBase* Goods);
};
