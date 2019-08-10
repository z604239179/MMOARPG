// Fill out your copyright notice in the Description page of Project Settings.

#include "SkillBase.h"
#include "PrimarySkill.h"
#include "CharacterBase.h"



USkillBase::USkillBase()
{
}



void USkillBase::InitSkill(AActor* Owner , UPrimarySkill* _Info)
{
	if (Owner&&_Info)
	{
		SkillInfo = _Info;
	}
}


