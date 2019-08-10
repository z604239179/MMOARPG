// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayStepSoundNotify.h"
#include "AudioDevice.h"
#include "CharacterBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

void UPlayStepSoundNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ACharacterBase* MyCharacter = Cast<ACharacterBase>(MeshComp->GetOwner());
	if (MyCharacter)
	{
		MyCharacter->PlayStepSound();
		/*FHitResult m_Hit;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(MyCharacter);
		QueryParams.bReturnPhysicalMaterial = true;
		GetWorld()->LineTraceSingleByChannel(m_Hit, MyCharacter->GetActorLocation(), MyCharacter->GetActorLocation() + FVector(0, 0, -500.f), ECC_Visibility, QueryParams);
		if (m_Hit.PhysMaterial != nullptr)
		{
			if (MyCharacter->StepSoundMap.Contains(m_Hit.PhysMaterial->SurfaceType))
			{
				GetWorld()->GetAudioDevice()->PlaySoundAtLocation(MyCharacter->StepSoundMap[m_Hit.PhysMaterial->SurfaceType], GetWorld(), 1.f, 1.f, 0, m_Hit.Location, FRotator::ZeroRotator);
			}
		}*/
	}

}
