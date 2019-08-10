// Fill out your copyright notice in the Description page of Project Settings.

#include "PassiveSkillBase.h"
#include "PPassiveSkill.h"
#include "BuffBase.h"
#include "MyAssetManager.h"

void UPassiveSkillBase::InitSkill(AActor* Owner, UPrimarySkill* _Info)
{
	Super::InitSkill(Owner, _Info);
	SkillInfo = Cast<UPPassiveSkill>(Super::GetBasicSkillInfo());
	SkillOwner = Cast<ACharacterBase>(Owner);

	for (auto& it : SkillInfo->BuffList)
	{
		UPBuff* TempBuffInfo = UMyAssetManager::FindObjectFromId<UPBuff>(it);
		UBuffBase* TempBuff = NewObject<UBuffBase>(this);
		TempBuff->InitSkill(SkillOwner, TempBuffInfo);
		BuffList.Add(TempBuff);
	}
}

void UPassiveSkillBase::ActivePassiveSkill()
{
	if (!bActive)
	{
		bActive = true;
		for (auto& it : BuffList)
		{
			//if(SkillOwner->GetSkillComponent()->AddBuffToList(it->GetBasicSkillInfo()->GetPrimaryAssetId(), it))
			it->ActiveBuff();
		}
	}
}

void UPassiveSkillBase::UnActivePassiveSkill()
{
	if (bActive)
	{
		for (auto& it : BuffList)
		{
			if (SkillOwner->GetSkillComponent()->RemoveBuffFromList(it))
			{
				it->UnactiveBuff();
			}
		}
		bActive = false;
	}
}
