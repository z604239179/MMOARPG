// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "MyAssetManager.h"
#include "DamageBoxBase.h"


AWeapon::AWeapon()
{
	CurrentState = EWeaponState::Free;
	UseCount = 0;
	bConstantUse = false;
	//CurrentCastSkill = nullptr;
}




void AWeapon::InitEquipment(FPrimaryAssetId EquipInfoId)
{
	Super::InitEquipment(EquipInfoId);
	UPrimaryEquip* TempEquipInfo = UMyAssetManager::FindObjectFromId<UPrimaryEquip>(EquipInfoId);
	if (TempEquipInfo)
	{
		if (TempEquipInfo->bIsWeapon)
		{
			UMyAssetManager& Manager = UMyAssetManager::Get();
			for (uint8 it = 0; it < TempEquipInfo->WeaponSkills.Num(); ++it)
			{
				UPWeponSkill* TempSkillInfo = Cast<UPWeponSkill>(Manager.GetPrimaryAssetObject(TempEquipInfo->WeaponSkills[it]));
				if (TempSkillInfo)
				{
					UWeaponSkillBase* TempSkill = NewObject<UWeaponSkillBase>(this, TempSkillInfo->SkillClass);
					if (TempSkill)
					{
						TempSkill->InitSkill(this, TempSkillInfo);
						Skills.Add(TempSkill);
					}
				}
			}
		}
	}
}


ADamageBoxBase* AWeapon::SpawnDamageBox()
{
	if (CurrentCastSkill)
	{
		//TODO: 解决服务器产生伤害盒子的问题

		UPWeponSkill* SkillInfoRef = CurrentCastSkill->GetSkillInfo();
		if (SkillInfoRef->DamageBoxClass)
		{
			if (Skills[UseCount]->GetSkillInfo()->SwingSound)
			{
				PlaySound(Skills[UseCount]->GetSkillInfo()->SwingSound, GetActorLocation());
			}
			ADamageBoxBase* NewDamageBox = GetWorld()->SpawnActorDeferred<ADamageBoxBase>(
				SkillInfoRef->DamageBoxClass,
				EquipmentOwner->GetDamageSpawnPoint()->GetComponentTransform(),
				this,
				EquipmentOwner,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


			NewDamageBox->InitDamageBox(SkillInfoRef->DamageType);
			if (SkillInfoRef->bDamageBoxAttach)
			{
				NewDamageBox->AttachToComponent(EquipmentOwner->GetDamageSpawnPoint(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
			}
			NewDamageBox->FinishSpawning(EquipmentOwner->GetDamageSpawnPoint()->GetComponentTransform());
			return NewDamageBox;
		}
	}
	return nullptr;
}


void AWeapon::ResetWeapon()
{
	GetWorld()->GetTimerManager().ClearTimer(ResetWeaponHandle);
	CurrentCastSkill = nullptr;
	CurrentState = EWeaponState::Free;
	UseCount = 0;
}

void AWeapon::ApplyDamageToPawn_Implementation(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass)
{
	if (DamagedActor && (BaseDamage != 0.f))
	{
		// make sure we have a good damage type
		TSubclassOf<UDamageType> const ValidDamageTypeClass = DamageTypeClass ? DamageTypeClass : TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		DamagedActor->TakeDamage(BaseDamage, DamageEvent, EventInstigator, DamageCauser);
	}

}

bool AWeapon::ApplyDamageToPawn_Validate(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass)
{
	return true;
}

void AWeapon::UseWeapon(bool bConstant)
{
	if (EquipmentOwner)
	{
		bConstantUse = bConstant;
		if (UseCount < Skills.Num())
		{
			GetWorld()->GetTimerManager().ClearTimer(ResetWeaponHandle);
			CurrentState = EWeaponState::Attack;
			CurrentCastSkill = Skills[UseCount];
			CurrentCastSkill->CastSkill();
			UseCount++;
			if (UseCount >= Skills.Num())
			{
				UseCount = 0;
			}
		}
	}
}

void AWeapon::StopUseWeapon()
{
	bConstantUse = false;
	if (CurrentCastSkill)
	{
		CurrentCastSkill->StopCast();
	}
}

void AWeapon::UseWeaponEnd(bool bInterrupted)
{
	if(bInterrupted)
	{
		GetWorld()->GetTimerManager().SetTimer(ResetWeaponHandle, this, &AWeapon::ResetWeapon, 1.5f);
	}
	else
	{
		ResetWeapon();
	}
}



void AWeapon::PlayEffect(ACharacterBase* DamageActor)
{
	if (DamageActor )
	{
		FHitResult AttackPoint;
		FCollisionQueryParams TempParams;
		TempParams.AddIgnoredActor(EquipmentOwner);
		TempParams.AddIgnoredActor(this);
		if (GetWorld()->LineTraceSingleByChannel(AttackPoint,
			GetMeshComponent()->GetSocketLocation(TEXT("Center")),
			DamageActor->GetActorLocation(),
			ECollisionChannel::ECC_Beem, TempParams))
		{
			AttackPoint.Location.Z = GetMeshComponent()->GetSocketLocation(TEXT("Center")).Z;

			
			/*播放粒子*/
			if (CurrentCastSkill->GetSkillInfo()->HitParticle)
			{
				PlayParticle(CurrentCastSkill->GetSkillInfo()->HitParticle,
					AttackPoint.Location,
					(GetActorLocation() - AttackPoint.Location).Rotation()
				);
			}
			if (DamageActor->GetActionState(ActionState::Parry))
			{
				/*播放被格挡声音*/
				if (CurrentCastSkill->GetSkillInfo()->BlockSound)
				{
					PlaySound(CurrentCastSkill->GetSkillInfo()->BlockSound,
						AttackPoint.Component->GetComponentLocation());
				}
			}
			else
			{
				/*播放声音*/
				if (CurrentCastSkill->GetSkillInfo()->HitSound)
				{
					PlaySound(CurrentCastSkill->GetSkillInfo()->HitSound,
						AttackPoint.Component->GetComponentLocation());
				}
			}
		}

	}
}


void AWeapon::PlayParticle_Implementation(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator)
{
		MultiPlayParticle(InParticle, PlayLocation, PlayRotator);
}
bool AWeapon::PlayParticle_Validate(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator)
{
	return true;
}

void AWeapon::PlaySound_Implementation(USoundBase* InSound, FVector PlayLocation)
{
	MultiPlaySound(InSound, PlayLocation);
}

bool AWeapon::PlaySound_Validate(USoundBase* InSound, FVector PlayLocation)
{
	return true;
}

void AWeapon::MultiPlayParticle_Implementation(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator)
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		InParticle,
		PlayLocation,
		PlayRotator);
}

void AWeapon::MultiPlaySound_Implementation(USoundBase* InSound, FVector PlayLocation)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(),
		InSound,
		PlayLocation);
}

