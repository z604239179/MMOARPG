// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARPG.h"
#include "GameFramework/Character.h"
#include"Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "HealthComponent.h"
#include "SkillComponent.h"
#include "EquipmentComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"


#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FTakeDamageHandle,AActor*, DamagedSource, float, Damage, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);



class UAnimMontage;
class AWeapon;
class ACharacterInfoBase;

UENUM()
enum class ECharacterType:uint8 
{Player,
Monster};

UENUM()
enum class EAttackState :uint8
{
	Free ,
	Left ,
	Right 
};

UENUM()
enum ActionState 
{
	Locking = 0x1,
	Dodging = 0x2,
	Attacking = 0x4,
	Castting = 0x8,
	Dead = 0x10,
	Limited = 0x20,
	Parry = 0x40,
	Block = 0x80,
	Max = 0xff
};

UCLASS()
class ARPG_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	/*��ǰ��ɫ����Ӫ����
	*Player		���
	*Monster	����
	*/
	UPROPERTY(Replicated)
	ECharacterType CharacterType;

	/*��ʼ����ɫ*/
	/*���ڷ������ϵ���*/
	UFUNCTION()
		virtual void InitCharacter() ;

protected:
	/*��ǰʹ��������״̬*/
	UPROPERTY(BlueprintReadOnly)
	EAttackState CurrentAttackState;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




	/*�˺��������������λ��*/
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
		class UArrowComponent* DamageSpawnPosision;	

	/*�����������������ֵ��ħ��ֵ������ֵ��ص�*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly ,Category = "Components")
		 class UHealthComponent* HealthComponent;

	/*����������������ͷš�BUFF�����*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class USkillComponent* SkillComp;		

	/*װ�����������װ�����*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UEquipmentComponent* EquipmentComp;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class USphereComponent* WaterCheckComp;

public:	
	

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* HatCloth;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* ArmorCloth;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* PantCloth;
	
	

		FORCEINLINE  UHealthComponent* GetHealthComponent() const {return HealthComponent;}

		FORCEINLINE  USkillComponent* GetSkillComponent() const { return SkillComp; }

		FORCEINLINE  UArrowComponent* GetDamageSpawnPoint() const { return DamageSpawnPosision; }
		
		FORCEINLINE  UEquipmentComponent* GetEquipmentComp() const { return EquipmentComp; }
		/*����ʵ��*/
		 UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
			 UAnimInstance* AnimInstance;




public:


	/*UFUNCTION(BlueprintPure)
		virtual int32 GetLWeaponType() { return (int32)EquipmentComp->GetLWeaponType(); }

	UFUNCTION(BlueprintPure)
		virtual int32 GetRWeaponType() { return (int32)EquipmentComp->GetLWeaponType(); }
*/
	/*��õ�ǰ��װ��������*/
	virtual AWeapon* GetLCurrentWeapon() { return EquipmentComp->GetLWeapon(); }

	virtual AWeapon* GetRCurrentWeapon() { return EquipmentComp->GetRWeapon(); }

	virtual AWeapon* GetCurrentUsedWeapon();


	/*���ŽŲ���*/
	UFUNCTION(BlueprintCallable)
		void PlayStepSound();

	UFUNCTION()
		void OnEnterWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	
	UFUNCTION()
		void OnLeaveWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
		TMap< TEnumAsByte<EPhysicalSurface>, USoundBase*> StepSoundMap;


protected:
	//Anim

	/*��������*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		 UAnimMontage* DodgeMontage;

	/*�ܵ���ͨ�����Ķ���*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		UAnimMontage* NormalHurtAnim;

	/*�ܵ����չ����Ķ���*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		UAnimMontage* FloatHurtAnim;

	/*�ܵ����������Ķ���*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		UAnimMontage* DownHurtAnim;

	/*������ʱ�Ķ���*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		UAnimMontage* BeBlockedAnim;

	/*�񵲶���*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Anim")
		UAnimMontage* ParryAnim;
protected:

	/*��ǰ������Ŀ��*/
	UPROPERTY(Replicated,BlueprintReadOnly)
		ACharacterBase* LockingTarget;

	/*�Ƿ�����*/
	ACharacterBase* BelockedCharacter;

public:
	FORCEINLINE ACharacterBase* GetLockingTarget()
	{
		return LockingTarget;
	}
	FORCEINLINE bool IsBeLocked()
	{
		return BelockedCharacter;
	}

	/*��ʼ��������*/
	UFUNCTION()
		virtual void LookAtTarget(ACharacterBase* LookTarget);

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerLookAtTarget(ACharacterBase* LookTarget);

	/*������������*/
	UFUNCTION()
		virtual void UnLookAtTarget();

	UFUNCTION(Reliable, Server, WithValidation)
		void ServerUnLookAtTarget();


	UFUNCTION(BlueprintCallable)
		FORCEINLINE ACharacterBase* GetLookingTarget() { return LockingTarget; }

protected:

	UFUNCTION(NetMulticast,Reliable)
		virtual void MultiDeath();
	/*����ʱִ��*/

	UPROPERTY(Replicated)
		uint8 ActionStates;

public:
	bool CanOprate()
	{
		return (ActionStates | ActionState::Locking)==ActionState::Locking;
	}
	UFUNCTION(BlueprintPure)
		bool GetActionState(ActionState InAction);


	UFUNCTION(Server, Reliable, WithValidation)
		void ResetActionState();

	UFUNCTION(Server,Reliable,WithValidation)
		void SetActionState(ActionState InAction,bool InState);

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		float FightSpeed;
	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		float WalkSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Attribute")
		float RunSpeed;

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
		virtual void Jumping();

	UFUNCTION(BlueprintCallable)
		virtual void Dodge(FVector DodgeVector);

	UFUNCTION()
		virtual void DodgeingEnd(UAnimMontage* animmontage, bool bInterrupted);

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
		virtual void ChangeSpeed(float NewSpeed);

	UFUNCTION(Server, Unreliable, WithValidation)
		void PlayMontage(UAnimMontage* ToPlay,FName SectionName = NAME_None);

	UFUNCTION(NetMulticast,Unreliable)
		void MultiPlayMontage(UAnimMontage* ToPlay, FName SectionName = NAME_None);

	//Attack

	UFUNCTION(BlueprintCallable)
		void UseWeapon(bool bLeft);

	UFUNCTION()
		void StopUseWeapon(bool bLeft);

	UFUNCTION(Reliable, Server,WithValidation)
		void UseWeaponEnd();

	UFUNCTION(BlueprintCallable, Reliable, NetMulticast)
		void CastSkill(uint8 SkillIndex);

	UFUNCTION(Server,Reliable,WithValidation)
		void CastSkillEnd();


	virtual void Death();

	FTakeDamageHandle OnTakeDamage;

protected:
	UFUNCTION(Reliable,Server,WithValidation)
		virtual void HandleGetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(Reliable, NetMulticast)
		void PlayHurtAnimation(const UDamageType* DamageType);


	UFUNCTION(BlueprintCallable)
		void ResetOprate();



public:
	UFUNCTION(BlueprintPure)
		virtual ACharacterInfoBase* GetCurrentInfoData() { return nullptr; }

	FORCEINLINE bool IsFalling() {return GetMovementComponent()->IsFalling();}

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

