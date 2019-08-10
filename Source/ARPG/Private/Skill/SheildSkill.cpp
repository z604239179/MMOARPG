// Fill out your copyright notice in the Description page of Project Settings.

#include "SheildSkill.h"
#include "CharacterBase.h"

void USheildSkill::Parring(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (!bInterrupted)
	{
		SkillOwner->EquipmentOwner->SetActionState(ActionState::Parry, true);
		SkillOwner->EquipmentOwner->PlayMontage(SkillInfo->SkillMontage, TEXT("Parring"));
	}
}

void USheildSkill::CastSkill()
{
	FOnMontageBlendingOutStarted ParringBeginDelegate;
	ParringBeginDelegate.BindUObject(this, &USheildSkill::Parring);
	SkillOwner->EquipmentOwner->PlayMontage(SkillInfo->SkillMontage,TEXT("ParryBegin"));
	SkillOwner->EquipmentOwner->AnimInstance->Montage_SetBlendingOutDelegate(ParringBeginDelegate, SkillInfo->SkillMontage);

}

void USheildSkill::StopCast()
{
	SkillOwner->EquipmentOwner->PlayMontage(SkillInfo->SkillMontage, TEXT("ParryEnd"));
	SkillOwner->EquipmentOwner->SetActionState(ActionState::Parry, false);
	SkillOwner->UseWeaponEnd(false);
	SkillOwner->EquipmentOwner->UseWeaponEnd();
}
