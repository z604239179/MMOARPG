// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/AI/PrimaryAI.h"
#include "PrimaryNPC.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPrimaryNPC : public UPrimaryAI
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "NPC")
		TMap<FPrimaryAssetId, int32> GoodsList;
};
