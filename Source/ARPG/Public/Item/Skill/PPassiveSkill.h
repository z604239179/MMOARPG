// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Skill/PrimarySkill.h"
#include "PPassiveSkill.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPPassiveSkill : public UPrimarySkill
{
	GENERATED_BODY()
public:
	UPPassiveSkill();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
		TArray<FPrimaryAssetId> BuffList;
};
