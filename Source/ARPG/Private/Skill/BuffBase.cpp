// Fill out your copyright notice in the Description page of Project Settings.

#include "BuffBase.h"
#include "PBuff.h"
#include "PlayerCharacter.h"

void UBuffBase::InitSkill(AActor* Owner, UPrimarySkill* _Info)
{
	Super::InitSkill(Owner, _Info);
	SkillInfo = Cast<UPBuff>(Super::GetBasicSkillInfo());
	BuffOwner = Cast<ACharacterBase>(Owner);
}

void UBuffBase::ActiveBuff()
{
	if (!bActive)
	{
		bActive = true;
		for (auto& it : SkillInfo->AddValueList)
		{
			BuffOwner->GetCurrentInfoData()->AddAttributefromName(it.Key, it.Value);
		}

		APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(BuffOwner);
		if (PlayerPawn)		/*是玩家角色*/
		{
			PlayerPawn->GetMyHUD()->AddBuff(SkillInfo);
		}
		GetWorld()->GetTimerManager().SetTimer(PersistentHandle, this, &UBuffBase::UnactiveBuff, SkillInfo->PersistentTime);
	}
}

void UBuffBase::UnactiveBuff()
{
	if (bActive)
	{
		for (auto& it : SkillInfo->AddValueList)
		{
			BuffOwner->GetCurrentInfoData()->SubAttributefromName(it.Key, it.Value);
		}

		APlayerCharacter* PlayerPawn = Cast<APlayerCharacter>(BuffOwner);
		if (PlayerPawn)		/*是玩家角色*/
		{
			PlayerPawn->GetMyHUD()->RemoveBuff(SkillInfo);
		}
		GetWorld()->GetTimerManager().ClearTimer(PersistentHandle);
		bActive = false;
	}
}
