// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/PrimaryItem.h"
#include "PrimarySkill.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class ARPG_API UPrimarySkill : public UPrimaryItem
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
		class UAnimMontage* SkillMontage;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
		TSubclassOf<class USkillBase> SkillClass;
};
