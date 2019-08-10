// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Skill/PrimarySkill.h"
#include "ARPG.h"
#include "PBuff.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPBuff : public UPrimarySkill
{
	GENERATED_BODY()
public:
	UPBuff();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
		TMap<EPropertyName, float> AddValueList;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buff")
		float PersistentTime;
};
