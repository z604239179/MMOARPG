// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PrimarySkill.h"
#include "PWeponSkill.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UPWeponSkill : public UPrimarySkill
{
	GENERATED_BODY()
public:

	UPWeponSkill();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
		UParticleSystem* HitParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
		USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
		USoundBase* BlockSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "FX")
		USoundBase* SwingSound;


	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		bool bDamageBoxAttach;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
		TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly,Category = "Damage")
		TSubclassOf<class ADamageBoxBase> DamageBoxClass;
};
