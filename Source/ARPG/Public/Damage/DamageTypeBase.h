// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "DamageTypeBase.generated.h"

/**
 * 
 */

UENUM()
enum class EDamageSubType : uint8
{
	None,
	HealthDamage,
	ManaDamage,
	StaminaDamage
};


UCLASS()
class ARPG_API UDamageTypeBase : public UDamageType
{
	GENERATED_BODY()

public:
		UDamageTypeBase();

		EDamageSubType DamageSubType;
};
