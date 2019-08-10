// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterSkillBase.h"
#include "SkillComponent.h"
#include "CharacterBase.h"
#include "PCharacterSkill.h"

UCharacterSkillBase::UCharacterSkillBase()
	:CurrentCD(0)
{

}

void UCharacterSkillBase::InitSkill(AActor* Owner, UPrimarySkill* _Info)
{
	Super::InitSkill(Owner, _Info);
	SkillInfo = Cast<UPCharacterSkill>(Super::GetBasicSkillInfo());
	SkillOwner = Cast<ACharacterBase>(Owner);
	MaxCD = SkillInfo->CD;
	if (SkillOwner)
	{
		OwnerComponent = SkillOwner->GetSkillComponent();
	}
	EndDelegate.BindUObject(this, &UCharacterSkillBase::OnCastEnd);
}

void UCharacterSkillBase::CastSkill()
{
	if (SkillInfo->SkillMontage&&bCanCast)
	{
		bCanCast = false;
		SkillOwner->PlayMontage(SkillInfo->SkillMontage);
		SkillOwner->AnimInstance->Montage_SetEndDelegate(EndDelegate, SkillInfo->SkillMontage);
		CurrentCD = 0;
		GetWorld()->GetTimerManager().SetTimer(SkillTimerHandle, this, &UCharacterSkillBase::ColdDown, 0.1f, true);
	}
}


void UCharacterSkillBase::OnCastEnd(UAnimMontage* AnimMontage, bool bInterrupted)
{
	if (OwnerComponent)
	{
		OwnerComponent->CastEnd(SkillIndex);
	}
}
void UCharacterSkillBase::ColdDown()
{
	if (CurrentCD < MaxCD)
	{
		CurrentCD = FMath::Clamp(CurrentCD, CurrentCD + 0.1f, MaxCD);
	}
	else
	{
		bCanCast = true;
		GetWorld()->GetTimerManager().ClearTimer(SkillTimerHandle);
	}
}


void UCharacterSkillBase::GetColdDownTime(float &CurrentTime, float &MaxTime)
{
	CurrentTime = CurrentCD;
	MaxTime = MaxCD;
	return;
}
