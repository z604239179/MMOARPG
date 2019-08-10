// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponSkillBase.h"
#include "PWeponSkill.h"
#include "Weapon.h"


void UWeaponSkillBase::InitSkill(AActor* Owner, UPrimarySkill* _Info)
{
	Super::InitSkill(Owner, _Info);
	SkillOwner = Cast<AWeapon>(Owner);
	SkillInfo = Cast<UPWeponSkill>(Super::GetBasicSkillInfo());
	EndDelegate.BindUObject(this, &UWeaponSkillBase::OnCastEnd);
}

void UWeaponSkillBase::CastSkill()
{
	SkillOwner->EquipmentOwner->PlayMontage(SkillInfo->SkillMontage);
	SkillOwner->EquipmentOwner->AnimInstance->Montage_SetEndDelegate(EndDelegate, SkillInfo->SkillMontage);

}



void UWeaponSkillBase::OnCastEnd(UAnimMontage* AnimMontage, bool bInterrupted)
{

	SkillOwner->UseWeaponEnd(bInterrupted);

}