// Fill out your copyright notice in the Description page of Project Settings.

#include "AIBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyAIController.h"
#include "MyAssetManager.h"
#include "PrimaryAI.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AAIBase::AAIBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->MaxWalkSpeed = 150.f;

	bUseControllerRotationYaw = true;

	bIsProtrol = false;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void AAIBase::BeginPlay()
{
	Super::BeginPlay();
	/*放置在世界中时，没有AIInfo*/
	if (!AIInfo)
	{
		AIInfo = UMyAssetManager::Get().FindObjectFromId<UPrimaryAI>(AIInfoClass);
	}


	if (AIInfo->mMesh&&AIInfo->AnimInstaceClass)
	{
		GetMesh()->SetSkeletalMesh(AIInfo->mMesh);
		GetMesh()->SetAnimInstanceClass(AIInfo->AnimInstaceClass);
	}

	if (HasAuthority())
	{
		if (bIsProtrol)
			CurrentState = EAIState::Protrol;
		else
			CurrentState = EAIState::Idle;

		FActorSpawnParameters SpawnInfo;
		SpawnInfo.Owner = this;
		SpawnInfo.Instigator = Instigator;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnInfo.ObjectFlags |= RF_Transient;	// We never want player states to save into a map

		CurrentInfoData = GetWorld()->SpawnActor<ACharacterInfoBase>(ACharacterInfoBase::StaticClass(), SpawnInfo);
		InitCharacter();
	}



}

// Called every frame
void AAIBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AAIBase::InitCharacter()
{

	UMyAssetManager& TempManager = UMyAssetManager::Get();
	for (auto& it : AIInfo->DefaultEquipmentList)
	{
		EquipmentComp->Equip(it.Value);
	}

	if (AIInfo->bCanFight)
	{
		for (auto&it : AIInfo->Attributes)
		{
			CurrentInfoData->SetBasicAttributes(it.Key, it.Value);
		}
	}

	Super::InitCharacter();

}




void AAIBase::LookAtTarget(ACharacterBase* LookTarget)
{
	Super::LookAtTarget(LookTarget);
	CurrentState = EAIState::Fight;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AAIBase::UnLookAtTarget()
{
	Super::UnLookAtTarget();
	if (bIsProtrol)
		CurrentState = EAIState::Protrol;
	else CurrentState = EAIState::Idle;
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->MaxWalkSpeed = 150.f;
}

void AAIBase::HandleGetDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Super::HandleGetDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	CurrentState = EAIState::Fight;
}

void AAIBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>&OutLifetimeProps)const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);



	// Value is already updated locally, skip in replication step

	DOREPLIFETIME(AAIBase, AIInfo);

	DOREPLIFETIME(AAIBase, CurrentInfoData);
	
	/* If we did not display the current inventory on the player mesh we couldoptimize replication by using this replication condition. */


}