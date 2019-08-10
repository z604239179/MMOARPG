// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/WeaponSkillBase.h"
#include "SheildSkill.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API USheildSkill : public UWeaponSkillBase
{
	GENERATED_BODY()
protected:

	UFUNCTION()
		void Parring(UAnimMontage* AnimMontage, bool bInterrupted);
public:
		virtual void CastSkill() override;

		virtual void StopCast() override;


};
