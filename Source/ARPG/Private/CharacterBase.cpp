// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterBase.h"
#include "MyPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "EngineUtils.h"
#include "Damage/NormalDamageType.h"
#include "Damage/FloatDamageType.h"
#include "Damage/DownDamageType.h"
#include "Damage/BlockDamageType.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.h"

#include"Net/UnrealNetwork.h"
#include "AudioDevice.h"
#include "GameFramework/PhysicsVolume.h"
#include "Components/SphereComponent.h"
#include "Water.h"
// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;



	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
	SkillComp = CreateDefaultSubobject<USkillComponent>(TEXT("SkillComp"));
	EquipmentComp = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComp"));
	EquipmentComp->SetIsReplicated(true);

	DamageSpawnPosision = CreateDefaultSubobject<UArrowComponent>(TEXT("DamageSpawnPosition"));
	DamageSpawnPosision->SetupAttachment(RootComponent);


	HealthComponent->SetupAttachment(RootComponent);
	HealthComponent->SetRelativeLocation(FVector(0, 0, 120.f));
	HealthComponent->SetDrawSize(FVector2D(100.f, 15.f));
	HealthComponent->SetWidgetSpace(EWidgetSpace::World);
	HealthComponent->SetVisibility(false);

	WaterCheckComp = CreateDefaultSubobject<USphereComponent>(TEXT("WaterCheckComp"));
	WaterCheckComp->SetupAttachment(RootComponent);
	WaterCheckComp->SetWorldTransform(GetMesh()->GetSocketTransform(FName("head")));
	WaterCheckComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	WaterCheckComp->SetCollisionObjectType(ECC_Pawn);
	WaterCheckComp->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	WaterCheckComp->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_DamageBox, ECR_Overlap);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Beem, ECR_Block);

	HatCloth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HatCloth"));
	ArmorCloth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArmorCloth"));
	PantCloth = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PantCloth"));
	HatCloth->SetupAttachment(GetMesh(), FName("head"));
	ArmorCloth->SetupAttachment(GetMesh(), FName("neck_01"));
	PantCloth->SetupAttachment(GetMesh(), FName("pelvis"));

	CharacterType = ECharacterType::Monster;
	CurrentAttackState = EAttackState::Free;
	bUseControllerRotationYaw = false;

	FightSpeed = 200.f;
	WalkSpeed = 300.f;
	RunSpeed = 450.f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	ActionStates = 0;
}

void ACharacterBase::InitCharacter()
{
	HealthComponent->InitHealthComponent();
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();	

	WaterCheckComp->OnComponentBeginOverlap.AddUniqueDynamic(this, &ACharacterBase::OnEnterWater);
	WaterCheckComp->OnComponentEndOverlap.AddUniqueDynamic(this, &ACharacterBase::OnLeaveWater);
	if (HasAuthority())
	{
		OnTakeAnyDamage.AddDynamic(this, &ACharacterBase::HandleGetDamage);
	}
	AnimInstance = GetMesh()->GetAnimInstance();
	
}



AWeapon* ACharacterBase::GetCurrentUsedWeapon()
{
	switch (CurrentAttackState)
	{
	case EAttackState::Free:
		return nullptr;
		break;
	case EAttackState::Left:
		return GetLCurrentWeapon();
		break;
	case EAttackState::Right:
		return GetRCurrentWeapon();
		break;
	}
	return nullptr;
}

void ACharacterBase::PlayStepSound()
{
	FHitResult m_Hit;
	FVector ORG = GetActorLocation();
	FVector End = FVector(ORG.X, ORG.Y, ORG.Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()-5.f);
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bReturnPhysicalMaterial = true;
	GetWorld()->LineTraceSingleByChannel(m_Hit, ORG, End, ECC_Visibility, QueryParams);
	if (m_Hit.PhysMaterial != nullptr)
	{
		if (StepSoundMap.Contains(m_Hit.PhysMaterial->SurfaceType))
		{
			GetWorld()->GetAudioDevice()->PlaySoundAtLocation(StepSoundMap[m_Hit.PhysMaterial->SurfaceType], GetWorld(), 1.f, 1.f, 0,GetActorLocation(), FRotator::ZeroRotator);
		}
	}
	
}

void ACharacterBase::OnEnterWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AWater* TempWater = Cast<AWater>(OtherActor);
	if (TempWater)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Swimming);
		GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = true;
	}
}

void ACharacterBase::OnLeaveWater(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AWater* TempWater= Cast<AWater>(OtherActor);
	if (TempWater)
	{
		/*FHitResult TempHitResult;
		FVector Org = GetActorLocation();
		FVector End = FVector(Org.X, Org.Y, Org.Z - GetCapsuleComponent()->GetScaledCapsuleHalfHeight()-30.f);
		FCollisionQueryParams TempParams;
		GetWorld()->LineTraceSingleByChannel(TempHitResult, Org, End, ECC_Visibility, TempParams);
		if (TempHitResult.bBlockingHit)
		{*/
			//GetCharacterMovement()->SetMovementMode(MOVE_Walking);
			GetCharacterMovement()->GetPhysicsVolume()->bWaterVolume = false;
		/*}*/
		
	}
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetActionState(ActionState::Locking) && LockingTarget)
	{
		
		if (!GetActionState((ActionState)(ActionState::Dodging | ActionState::Limited)))
		{
			if (!LockingTarget->GetActionState(ActionState::Dead))
			{
				FRotator YawRotator = FMath::Lerp(GetActorRotation(), ((LockingTarget->GetActorLocation() - GetActorLocation()).Rotation()), 0.2f);
				YawRotator.Pitch = 0;
				YawRotator.Roll = 0;
				SetActorRotation(YawRotator);
			}
		}
	}
}


void ACharacterBase::LookAtTarget(ACharacterBase* LookTarget)
{
	if (LookTarget)
	{
		if (!LookTarget->GetActionState(ActionState::Dead))
		{
			ServerLookAtTarget(LookTarget);
			LookTarget->BelockedCharacter = this;
		}
	}
}


void ACharacterBase::ServerLookAtTarget_Implementation(ACharacterBase* LookTarget)
{

	LockingTarget = LookTarget;
	SetActionState(ActionState::Locking, true);
	GetCharacterMovement()->MaxWalkSpeed = FightSpeed;

}
bool ACharacterBase::ServerLookAtTarget_Validate(ACharacterBase* LookTarget)
{
	return true;
}


void ACharacterBase::UnLookAtTarget()
{
	if (LockingTarget)
	{
		LockingTarget->BelockedCharacter = nullptr;
		ServerUnLookAtTarget();
	}
}


void ACharacterBase::ServerUnLookAtTarget_Implementation()
{
	SetActionState(ActionState::Locking, false);
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	LockingTarget = nullptr;
}

bool ACharacterBase::ServerUnLookAtTarget_Validate()
{
	return true;
}

void ACharacterBase::Jumping_Implementation()
{
	if (CanOprate())
	{
		Super::Jump();
	}
}

void ACharacterBase::Dodge(FVector DodgeVector)
{
	if (CanOprate()&& DodgeMontage)
	{
		SetActionState(ActionState::Dodging, true);
		SetActorRotation(DodgeVector.Rotation());
		PlayMontage(DodgeMontage);
		AnimInstance->Montage_GetBlendingOutDelegate(DodgeMontage)->BindUObject(this, &ACharacterBase::DodgeingEnd);
	}
}



void ACharacterBase::DodgeingEnd(UAnimMontage* animmontage, bool bInterrupted)
{
	SetActionState(ActionState::Dodging, false);
}


bool ACharacterBase::GetActionState(ActionState InAction)
{
	return ActionStates & InAction;
}

void ACharacterBase::ResetActionState_Implementation()
{
	ActionStates = 0;
}

bool ACharacterBase::ResetActionState_Validate()
{
	return true;
}



void ACharacterBase::SetActionState_Implementation(ActionState InAction, bool InState)
{
	if (InState)
	{
		//ÖÃÎªtrue
		ActionStates |= InAction;
	}
	else
	{
		//ÖÃÎªfalse
		ActionStates &= ~InAction;
	}
}

bool ACharacterBase::SetActionState_Validate(ActionState InAction, bool InState)
{
	return true;
}


void ACharacterBase::PlayMontage_Implementation(UAnimMontage* ToPlay, FName SectionName)
{
	MultiPlayMontage(ToPlay, SectionName);
}

bool ACharacterBase::PlayMontage_Validate(UAnimMontage* ToPlay, FName SectionName)
{
	return true;
}



void ACharacterBase::MultiPlayMontage_Implementation(UAnimMontage* ToPlay, FName SectionName = NAME_None)
{
	if (AnimInstance&&ToPlay)
	{
		AnimInstance->Montage_Play(ToPlay);
		if (SectionName != NAME_None)
		{
			AnimInstance->Montage_JumpToSection(SectionName);
		}
	}
}

void ACharacterBase::UseWeapon(bool bLeft)
{
	if (CanOprate()&&!IsFalling()&&CurrentAttackState == EAttackState::Free)
	{
		if (bLeft)
		{
			if (GetLCurrentWeapon())
			{
				CurrentAttackState = EAttackState::Left;
				SetActionState(ActionState::Attacking, true);
				SetActorRotation(FRotator(0, GetControlRotation().Yaw, 0));
				GetLCurrentWeapon()->UseWeapon();
			}
		}
		else
		{
			if (GetRCurrentWeapon())
			{
				CurrentAttackState = EAttackState::Right;
				SetActorRotation(FRotator(0, GetControlRotation().Yaw, 0));
				SetActionState(ActionState::Attacking, true);
				GetRCurrentWeapon()->UseWeapon();


			}
		}
	}
}


void ACharacterBase::StopUseWeapon(bool bLeft)
{
	if (bLeft)
	{
		if (GetLCurrentWeapon())
			GetLCurrentWeapon()->StopUseWeapon();
	}
	else
	{
		{
			if (GetRCurrentWeapon())
				GetRCurrentWeapon()->StopUseWeapon();
		}
	}
}

void ACharacterBase::UseWeaponEnd_Implementation()
{

	SetActionState(ActionState::Attacking, false);
	CurrentAttackState = EAttackState::Free;

}

bool ACharacterBase::UseWeaponEnd_Validate()
{
	return true;
}


void ACharacterBase::ChangeSpeed_Implementation(float NewSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewSpeed;
}


void ACharacterBase::CastSkill_Implementation(uint8 SkillIndex)
{
	if (CanOprate())
	{
		SetActionState(ActionState::Castting, true);
		SkillComp->CastSkill(SkillIndex);

	}
}


void ACharacterBase::CastSkillEnd_Implementation()
{
	SetActionState(ActionState::Castting, false);
}



bool ACharacterBase::CastSkillEnd_Validate()
{
	return true;
}

void ACharacterBase::Death()
{
	if (HasAuthority())
	{
		EquipmentComp->DestroyAllEquipment(10.0f);

		SetActionState(ActionState::Dead, true);
		MultiDeath();
	}
}


void ACharacterBase::MultiDeath_Implementation()
{
	if (BelockedCharacter)
	{
		BelockedCharacter->UnLookAtTarget();
	}
	AnimInstance->StopAllMontages(0.2f);
	GetCharacterMovement()->StopMovementImmediately();
	DetachFromControllerPendingDestroy();
	if (GetActionState(ActionState::Locking))
	{
		UnLookAtTarget();
	}
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	SetLifeSpan(10.0f);

	EquipmentComp->DestroyAllEquipment(10.f);

}






void ACharacterBase::HandleGetDamage_Implementation(AActor* DamagedActor,const float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (!GetActionState(ActionState::Dead))
	{
		float ApplayDamage = Damage;
		if (GetActionState(ActionState::Parry) || GetActionState(ActionState::Block))
		{
			ApplayDamage = 0;
		}
		else
		{
			SetActionState(ActionState(Attacking | Castting | Dodging), false);
			CurrentAttackState = EAttackState::Free;
		}
		OnTakeDamage.Broadcast(DamagedActor, ApplayDamage, DamageType, InstigatedBy, DamageCauser);

		if (!GetActionState(ActionState::Dead))
		{
			PlayHurtAnimation(DamageType);
		}
	}
	
}

bool ACharacterBase::HandleGetDamage_Validate(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	return true;
}


void ACharacterBase::PlayHurtAnimation_Implementation(const UDamageType* DamageType)
{
	if (AnimInstance)
	{
		if (!GetActionState(ActionState::Parry))
		{
			SetActionState(ActionState::Limited, true);

			if (Cast<UNormalDamageType>(DamageType))
			{
				if (NormalHurtAnim)
				{
					AnimInstance->Montage_Play(NormalHurtAnim);
					return;
				}
			}

			if (Cast<UFloatDamageType>(DamageType))
			{
				if (FloatHurtAnim)
				{
					AnimInstance->Montage_Play(FloatHurtAnim);
					LaunchCharacter(GetActorUpVector()*800.f, false, true);
					return;
				}
			}

			if (Cast<UDownDamageType>(DamageType))
			{
				if (DownHurtAnim)
				{
					AnimInstance->Montage_Play(DownHurtAnim);
					return;
				}
			}
			if (Cast<UBlockDamageType>(DamageType))
			{
				if (BeBlockedAnim)
				{
					AnimInstance->Montage_Play(BeBlockedAnim);
					return;
				}
			}


			ResetOprate();

		}
	}
}


void ACharacterBase::ResetOprate()
{
	SetActionState(ActionState::Limited, false);
}




void ACharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);



	// Value is already updated locally, skip in replication step

	DOREPLIFETIME(ACharacterBase, ActionStates); 
	DOREPLIFETIME(ACharacterBase, LockingTarget);
	DOREPLIFETIME(ACharacterBase, CharacterType);
	
	
	/* If we did not display the current inventory on the player mesh we couldoptimize replication by using this replication condition. */


}