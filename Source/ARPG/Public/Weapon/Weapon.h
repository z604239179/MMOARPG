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

	/*武器当前状态*/
	EWeaponState CurrentState;

	UPROPERTY()
		TArray<UWeaponSkillBase*> Skills;

	uint8 UseCount;


	bool bConstantUse;

	UPROPERTY()
	UWeaponSkillBase* CurrentCastSkill;


public:
	virtual void InitEquipment(FPrimaryAssetId EquipInfoId) override;

	/*网络中播放粒子*/
	UFUNCTION(Server, Unreliable,WithValidation)
		void PlayParticle(UParticleSystem* InParticle, FVector PlayLocation, FRotator PlayRotator);

	/*网络中播放声音*/
	UFUNCTION(Server, Unreliable,WithValidation)
		void PlaySound(USoundBase* InSound, FVector PlayLocation);

	/*网络中造成伤害*/
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
	/*跳跃攻击*/
	virtual void JumppingAttack() {};

	virtual void UseWeapon(bool bConstant=false);

	virtual void StopUseWeapon();

	virtual void UseWeaponEnd(bool bInterrupted);

	/*产生伤害时产生的特效*/
	virtual void PlayEffect(ACharacterBase* DamageActor);


};
