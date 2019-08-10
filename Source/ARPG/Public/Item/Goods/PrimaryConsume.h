// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Goods/PrimaryGoods.h"
#include "ARPG.h"
#include "PrimaryConsume.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPrimaryConsume : public UPrimaryGoods
{
	GENERATED_BODY()
public:
	UPrimaryConsume();

	UPROPERTY(EditDefaultsOnly)
		TMap<EPropertyName, float> PropertyAddList;
	
};
