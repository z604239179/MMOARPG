// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Skill/SkillBase.h"
#include "SkillCastInterface.h"
#include "WeaponSkillBase.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UWeaponSkillBase : public USkillBase,public ISkillCastInterface
{
	GENERATED_BODY()
protected:
	class AWeapon* SkillOwner;

	class UPWeponSkill* SkillInfo;


public:
	/*施放技能相关*/
	virtual void InitSkill(AActor* Owner, UPrimarySkill* _Info);
	virtual void StopCast() override {};
	virtual void CastSkill() override;

	UFUNCTION()
		virtual void OnCastEnd(UAnimMontage* AnimMontage, bool bInterrupted) override;


	FORCEINLINE UPWeponSkill* GetSkillInfo() const { return SkillInfo; }
};
