// Fill out your copyright notice in the Description page of Project Settings.

#include "DamageNotifyState.h"
#include "CharacterBase.h"
#include "DamageBoxBase.h"
#include "Weapon.h"
void UDamageNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	ACharacterBase*	OwnCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (OwnCharacter)
	{
		if (OwnCharacter->GetCurrentUsedWeapon())
		{
			SpawnedDamageBox = OwnCharacter->GetCurrentUsedWeapon()->SpawnDamageBox();
		}
	}
}

void UDamageNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (SpawnedDamageBox)
	{
		SpawnedDamageBox->Destroy();
	}
	if (MeshComp->GetOwner())
	{
		ACharacterBase* OwnCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
		if (OwnCharacter)
		{
			OwnCharacter->UseWeaponEnd();
		}
	}
}
