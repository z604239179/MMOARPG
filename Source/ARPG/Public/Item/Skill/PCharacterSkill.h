// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimarySkill.h"
#include "PCharacterSkill.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPCharacterSkill : public UPrimarySkill
{
	GENERATED_BODY()

public:
	UPCharacterSkill();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Skill")
		float CD;

};
