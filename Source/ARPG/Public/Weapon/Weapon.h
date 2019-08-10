// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment.h"
#include "Kismet/GameplayStatics.h"
#include "PWeponSkill.h"
#include "WeaponSkillBase.h"
#include "Weapon.generated.h"

UENUM()
enum class EWeaponState : uint8
{
	Free,
	Attack,
	Jumpping
};

class ACharacterBase;

UCLASS()
class ARPG_API AWeapon : public AEquipment
{
	GENERATED_BODY()
public:
		AWeapon();
protected:

	/*������ǰ״̬*/
	EWeaponState CurrentState;

	UPROPERTY()
		TArray<UWeaponSkillBase*> Skills;

	uint8 UseCount;


	bool bConstantUse;

	UPROPERTY()
	UWeaponSkillBase* CurrentCastSkill;


public:
	virtual void InitEquipment(FPrimaryAssetId EquipInfoId) override;

	/*�����в�������*/
	UFUNCTION(Server, Unreliable,WithValidation)
		void PlayParticle(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator);

	/*�����в�������*/
	UFUNCTION(Server, Unreliable,WithValidation)
		void PlaySound(USoundBase* InSound, FVector PlayLocation);

	/*����������˺�*/
	UFUNCTION(Server, Reliable, WithValidation)
		void ApplyDamageToPawn(AActor* DamagedActor, float BaseDamage, AController* EventInstigator, AActor* DamageCauser, TSubclassOf<UDamageType> DamageTypeClass);



	ADamageBoxBase* SpawnDamageBox();

	
protected:

	FTimerHandle ResetWeaponHandle;
	UFUNCTION()
		void ResetWeapon();

	UFUNCTION(NetMulticast, Reliable)
		void MultiPlayParticle(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator);
	UFUNCTION(NetMulticast, Reliable)
		void MultiPlaySound(USoundBase* InSound, FVector PlayLocation);

public:
	/*��Ծ����*/
	virtual void JumppingAttack() {};

	virtual void UseWeapon(bool bConstant=false);

	virtual void StopUseWeapon();

	virtual void UseWeaponEnd(bool bInterrupted);

	/*�����˺�ʱ��������Ч*/
	virtual void PlayEffect(ACharacterBase* DamageActor);


};
